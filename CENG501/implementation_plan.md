# C-CLIP: Multimodal Continual Learning — Implementation Plan

Reproduce the C-CLIP method (ICLR 2025) end-to-end, matching paper results.

> [!IMPORTANT]
> Official repo: https://github.com/SmallPigPeppa/C-CLIP — We will use it as reference but write our own clean implementation.

---

## Milestone 0 — Project Scaffolding

### 0.1 Create project directory structure

```
CENG501/
├── c_clip/
│   ├── __init__.py
│   ├── config.py            # All hyperparams & paths in one place
│   ├── data/
│   │   ├── __init__.py
│   │   ├── transforms.py    # Universal image/text transform
│   │   ├── base_dataset.py  # Abstract base for all datasets
│   │   ├── flickr30k.py
│   │   ├── coco.py
│   │   ├── pets.py
│   │   ├── lexica.py
│   │   ├── simpsons.py
│   │   ├── wikiart.py
│   │   ├── kream.py
│   │   ├── sketch.py
│   │   ├── havg.py
│   │   ├── classification.py  # ImageNet, CIFAR-100, etc.
│   │   └── split_utils.py     # Seed-based train/test splitting
│   ├── model/
│   │   ├── __init__.py
│   │   ├── clip_wrapper.py   # Base CLIP loading & feature extraction
│   │   ├── lora.py           # LoRA injection & merge logic
│   │   ├── projector.py      # The h_ψ MLP projector
│   │   └── c_clip.py         # Full C-CLIP model orchestrator
│   ├── losses/
│   │   ├── __init__.py
│   │   ├── clip_loss.py      # Standard symmetric cross-entropy
│   │   └── ckc_loss.py       # Contrastive Knowledge Consolidation
│   ├── evaluation/
│   │   ├── __init__.py
│   │   ├── retrieval.py      # I2T & T2I Recall@K
│   │   └── classification.py # Zero-shot classification accuracy
│   ├── training/
│   │   ├── __init__.py
│   │   ├── trainer.py        # Main training loop
│   │   ├── optimizer.py      # AdamW + stage-wise LR config
│   │   └── scheduler.py      # Cosine decay with warmup
│   └── utils/
│       ├── __init__.py
│       ├── logging.py
│       └── checkpointing.py
├── scripts/
│   ├── download_datasets.py
│   ├── prepare_splits.py
│   ├── run_baseline.py
│   ├── run_cclip.py
│   └── evaluate.py
├── configs/
│   └── default.yaml
├── requirements.txt
└── README.md
```

### 0.2 Create `requirements.txt`

```
torch>=2.0
torchvision
transformers
peft
datasets
open_clip_torch
Pillow
numpy
scipy
tqdm
wandb
PyYAML
```

### 0.3 Create virtual environment & install dependencies

```bash
python3 -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
```

### 0.4 Create `config.py` — Centralized configuration

All hyperparams in one file:
- `IMAGE_SIZE = 224`
- `MAX_TEXT_LEN = 77`
- `BATCH_SIZE = 1024` (or 256 for ViT-L)
- `EPOCHS = 40`
- `WARMUP_EPOCHS = 5`
- `LORA_RANK = 16`
- `LORA_ALPHA = 32` (2×R)
- `LORA_DROPOUT = 0.1`
- `MERGE_ALPHA = 0.5`
- `WEIGHT_DECAY = 0.2`
- `BETA1 = 0.9`, `BETA2 = 0.99`
- `RANDOM_SEED = 42`
- Dataset-specific LRs (sub-task 4.3)
- Task order: `[flickr30k, coco, pet, lexica, simpsons, wikiart, kream, sketch]`
- Dataset paths, checkpoint paths

---

## Milestone 1 — Data Engineering & the VLCL Benchmark

> [!NOTE]
> 15 total datasets: 8 for continual training, 1 for zero-shot retrieval, 6 for zero-shot classification.

---

### 1.1 Build the universal image transform pipeline

- **File**: `c_clip/data/transforms.py`
- Resize all images to `224×224`
- Use CLIP-standard normalization: `mean=[0.48145466, 0.4578275, 0.40821073]`, `std=[0.26862954, 0.26130258, 0.27577711]`
- Convert PIL → Tensor
- No data augmentation (paper doesn't mention any beyond resize)

### 1.2 Build the universal text tokenizer wrapper

- **File**: `c_clip/data/transforms.py`
- Use `CLIPTokenizer` from HuggingFace (`openai/clip-vit-base-patch16`)
- Truncate/pad all text to exactly **77 tokens**
- Return `input_ids` and `attention_mask`

### 1.3 Create the abstract `BaseImageTextDataset` class

- **File**: `c_clip/data/base_dataset.py`
- Abstract PyTorch `Dataset` that returns `(image_tensor, text_token_ids, attention_mask)`
- Applies image transform and text tokenizer from 1.1/1.2
- Subclasses only need to implement `_load_samples() → list[(image_path, caption)]`

### 1.4 Write seed-based splitting utility

- **File**: `c_clip/data/split_utils.py`
- Function `split_dataset(samples, train_ratio, seed=42)` → `(train_samples, test_samples)`
- Uses `numpy.random.RandomState(seed)` for reproducibility
- Will be used by Simpsons, WikiArt, Sketch (80/20) and Kream (50/50)

---

### Track A: Multimodal Continual Learning Datasets (8 datasets)

#### 1.5 Flickr30K dataset loader

- **File**: `c_clip/data/flickr30k.py`
- Source: HuggingFace `nlphuji/flickr30k` or official download
- Pre-defined test set: **1K test images** (standard Flickr30K test split)
- Each image has 5 captions — use all 5 during eval, pick one randomly during training
- Subclass `BaseImageTextDataset`

#### 1.6 COCO-caption dataset loader

- **File**: `c_clip/data/coco.py`
- Source: HuggingFace or COCO 2014 official
- Pre-defined test set: **5K test images** (Karpathy split)
- 5 captions per image — same strategy as Flickr30K
- Subclass `BaseImageTextDataset`

#### 1.7 Oxford Pets dataset loader

- **File**: `c_clip/data/pets.py`
- Source: `torchvision.datasets.OxfordIIITPet` or HuggingFace
- Needs image-caption pairs → generate captions from class label: `"A photo of a {breed}"`
- Use official train/test split
- Subclass `BaseImageTextDataset`

#### 1.8 Lexica dataset loader

- **File**: `c_clip/data/lexica.py`
- Source: HuggingFace (Shen et al., 2024) — AI-generated images with prompts
- Use official test set
- Subclass `BaseImageTextDataset`

#### 1.9 Simpsons dataset loader

- **File**: `c_clip/data/simpsons.py`
- Source: HuggingFace `Norod78/simpsons-blip-captions` (image + BLIP caption)
- **Custom split: 80% train / 20% test** (seed=42)
- Subclass `BaseImageTextDataset`

#### 1.10 WikiArt dataset loader

- **File**: `c_clip/data/wikiart.py`
- Source: HuggingFace (wikiart with captions) or Kaggle
- **Custom split: 80% train / 20% test** (seed=42)
- Subclass `BaseImageTextDataset`

#### 1.11 Kream dataset loader

- **File**: `c_clip/data/kream.py`
- Source: HuggingFace `hahminlew/kream-product-blip-captions`
- **Custom split: 50% train / 50% test** (seed=42)
- Subclass `BaseImageTextDataset`

#### 1.12 Sketch (FS-COCO) dataset loader

- **File**: `c_clip/data/sketch.py`
- Source: FS-COCO dataset (Chowdhury et al., 2022) — freehand sketches + captions
- **Custom split: 80% train / 20% test** (seed=42)
- Subclass `BaseImageTextDataset`

#### 1.13 Write `download_datasets.py` script for all 8 continual datasets

- **File**: `scripts/download_datasets.py`
- Automates downloading each dataset to `data/` directory
- Uses HuggingFace `datasets` library where possible
- Prints summary stats (num samples, train/test sizes)

#### 1.14 Write `prepare_splits.py` script

- **File**: `scripts/prepare_splits.py`
- For each custom-split dataset (Simpsons, WikiArt, Sketch, Kream):
  - Calls `split_dataset()` with correct ratio and seed
  - Saves split indices to JSON for reproducibility
- Verifies Flickr30K and COCO use their standard test splits

---

### Track B: Zero-Shot Retrieval Dataset (1 dataset)

#### 1.15 HausaVG (HAVG) dataset loader

- **File**: `c_clip/data/havg.py`
- Source: HuggingFace `HausaNLP/HausaVG`
- Hausa-language captioned subset of Visual Genome
- Use the official test set for zero-shot retrieval evaluation
- Subclass `BaseImageTextDataset`

---

### Track C: Zero-Shot Classification Datasets (6 datasets)

#### 1.16 Classification dataset wrapper

- **File**: `c_clip/data/classification.py`
- Create a unified `ZeroShotClassificationDataset` class
- For each dataset, store: `(image, label_index, class_name)`
- Build text prompts from class names: `"A photo of a {class_name}."`

#### 1.17 ImageNet-1K loader

- Uses `torchvision.datasets.ImageNet` or HF `imagenet-1k`
- Use validation set (50K images, 1000 classes)
- Must include the standard 1000 class name list (from CLIP's original eval)

#### 1.18 CIFAR-100 loader

- Uses `torchvision.datasets.CIFAR100`
- Use test set (10K images, 100 classes)

#### 1.19 StanfordCars loader

- Uses `torchvision.datasets.StanfordCars` or HF
- Use test set

#### 1.20 Flowers-102 loader

- Uses `torchvision.datasets.Flowers102` or HF
- Use test set

#### 1.21 DTD (Describable Textures) loader

- Uses `torchvision.datasets.DTD` or HF
- Use test set

#### 1.22 Food-101 loader

- Uses `torchvision.datasets.Food101` or HF
- Use test set

#### 1.23 Create `DataLoader` factory function

- **File**: `c_clip/data/__init__.py`
- `get_dataloader(dataset_name, split, batch_size, num_workers)` → `DataLoader`
- Central entry point for all dataset access
- Handles train/test split selection automatically

#### 1.24 Verify all datasets load correctly — smoke test

- Write a quick script that iterates one batch from each of the 15 datasets
- Check shapes: image `(B, 3, 224, 224)`, tokens `(B, 77)`, masks `(B, 77)`
- Print first caption decoded back to text as sanity check

---

## Milestone 2 — Evaluation Engine & Baseline Validation

> [!IMPORTANT]
> We must confirm CLIP ViT-B/16 gives exactly **67.73% zero-shot accuracy on ImageNet-1K** before proceeding. This is the paper's stated baseline.

---

### 2.1 Load pre-trained CLIP ViT-B/16

- **File**: `c_clip/model/clip_wrapper.py`
- Load `openai/clip-vit-base-patch16` from HuggingFace `transformers`
- Expose methods: `encode_image(images) → features`, `encode_text(tokens) → features`
- L2-normalize features by default
- Move to GPU, set to eval mode

### 2.2 Implement Recall@K for image-text retrieval

- **File**: `c_clip/evaluation/retrieval.py`
- `compute_retrieval_metrics(image_features, text_features, k_values=[1, 5, 10])`
- Compute similarity matrix: `S = image_features @ text_features.T`
- **I2T Recall@1**: For each image row, check if correct text is the top-1 match
- **T2I Recall@1**: For each text column, check if correct image is the top-1 match
- Handle multi-caption datasets (5 captions per image → any hit counts as correct for I2T)
- Return dict: `{i2t_r1, i2t_r5, i2t_r10, t2i_r1, t2i_r5, t2i_r10}`

### 2.3 Implement retrieval evaluation loop

- **File**: `c_clip/evaluation/retrieval.py`
- `evaluate_retrieval(model, dataloader)` → extracts all features, calls `compute_retrieval_metrics`
- Handles batched feature extraction to avoid OOM
- Concatenates all batch features before computing similarity matrix

### 2.4 Implement zero-shot classification engine

- **File**: `c_clip/evaluation/classification.py`
- `evaluate_zero_shot(model, dataloader, class_names, templates=None)`
- Step 1: Encode all class text prompts → text_features `(num_classes, d)`
- Step 2: For each image batch, compute similarity with all class features
- Step 3: argmax → predicted class, compare with ground truth
- Return accuracy (%)
- Support prompt ensembling with multiple templates (e.g., "A photo of a {}", "A picture of a {}")

### 2.5 Build the CLIP prompt template lists

- **File**: `c_clip/evaluation/classification.py`
- Use CLIP's standard 80 prompt templates for ImageNet
- Simpler templates for other datasets: `"A photo of a {class_name}."`
- Store per-dataset template lists

### 2.6 Create unified evaluation function

- **File**: `c_clip/evaluation/__init__.py`
- `run_full_evaluation(model, stage_index=None)`
- Evaluates all 3 tracks:
  1. I2T R@1 and T2I R@1 on all 8 continual datasets
  2. I2T R@1 on HAVG (zero-shot retrieval)
  3. Accuracy on all 6 classification datasets
- Returns structured results dict + prints formatted table
- Logs to wandb if enabled

### 2.7 Baseline validation script

- **File**: `scripts/run_baseline.py`
- Load CLIP ViT-B/16
- Run `run_full_evaluation(model, stage_index=0)` (before any training)
- **Checkpoint**: Verify ImageNet accuracy ≈ 67.73%
- **Checkpoint**: Verify CIFAR-100 accuracy ≈ 66.87%
- **Checkpoint**: Verify Flickr30K I2T R@1 ≈ 35.80%, T2I R@1 ≈ 55.88%
- **Checkpoint**: Verify COCO I2T R@1 ≈ 10.40%, T2I R@1 ≈ 28.32% (from Table 3)
- If these numbers are off by more than 0.5%, STOP and debug

### 2.8 Implement per-stage evaluation tracker

- **File**: `c_clip/evaluation/__init__.py`
- `EvaluationTracker` class that stores results after each stage
- Can compute Performance Degradation (PD) = accuracy at stage 0 minus accuracy at final stage
- Generates comparison table similar to Table 4 in the paper

---

## Milestone 3 — The C-CLIP Architecture

---

### 3.1 LoRA injection using HuggingFace `peft`

- **File**: `c_clip/model/lora.py`
- Function `inject_lora(model, rank=16, alpha=32, dropout=0.1) → PeftModel`
- Apply LoRA to **both** vision encoder and text encoder
- Target modules: all `q_proj`, `k_proj`, `v_proj`, `out_proj` in attention layers
- Also target `fc1`, `fc2` if used in the paper (MLPs within transformer blocks)
- Use `peft.LoraConfig` and `peft.get_peft_model()`

### 3.2 LoRA merge function

- **File**: `c_clip/model/lora.py`
- `merge_lora(model, alpha=0.5)`
- For each LoRA layer: `W_merged = W_frozen + alpha * (B @ A)`
- This permanently modifies the base weights
- After merge, remove the LoRA adapters from the model
- Re-initialize fresh LoRA layers for the next task

### 3.3 LoRA state reset function

- **File**: `c_clip/model/lora.py`
- `reset_lora(model, rank=16, alpha=32, dropout=0.1)`
- Drop current LoRA weights, inject fresh zero-initialized LoRA
- Called after `merge_lora()` at the end of each task stage

### 3.4 Build the Projector MLP (h_ψ)

- **File**: `c_clip/model/projector.py`
- `ProjectorMLP(input_dim, hidden_dim, output_dim)`
- Architecture: Linear → ReLU → Linear → ReLU → Linear
  (standard 3-layer MLP projector as commonly used in contrastive learning)
- `input_dim = 512` (CLIP ViT-B/16 feature dim)
- `hidden_dim = 512` (same as feature dim, typical choice)
- `output_dim = 512`
- The projector maps features from the new model into a space for CKC loss

### 3.5 CLIP wrapper — feature extraction methods

- **File**: `c_clip/model/clip_wrapper.py`
- `CLIPWrapper` class:
  - `__init__(model_name='openai/clip-vit-base-patch16')`
  - `get_image_features(images) → z_v` (normalized)
  - `get_text_features(input_ids, attention_mask) → z_c` (normalized)
  - `get_image_features_raw(images) → z_v` (unnormalized, for projector)
  - `get_text_features_raw(input_ids, attention_mask) → z_c` (unnormalized, for projector)

### 3.6 Model state management — old model snapshot

- **File**: `c_clip/model/c_clip.py`
- `CCLIPModel` class:
  - `self.model` — the trainable current model (with LoRA)
  - `self.old_model` — frozen copy from end of previous task (no LoRA)
  - `self.projector` — shared MLP projector
  - Method `snapshot_old_model()`:
    - Deep-copy current model state (after LoRA merge)
    - Freeze all parameters (`requires_grad=False`)
    - Store as `self.old_model`
  - Method `is_first_task() → bool` (no old model exists yet)

### 3.7 Full forward pass for C-CLIP

- **File**: `c_clip/model/c_clip.py`
- `CCLIPModel.forward(images, text_ids, text_mask)` returns:
  - `z_v_new`: normalized image features from new model
  - `z_c_new`: normalized text features from new model
  - `h_v_new`: projected image features from new model through projector
  - `h_c_new`: projected text features from new model through projector
  - `z_v_old`: normalized image features from old model (frozen, no grad)
  - `z_c_old`: normalized text features from old model (frozen, no grad)
- First task: only returns new features (no old model yet)

### 3.8 Parameter counting utility

- **File**: `c_clip/utils/__init__.py`
- `count_parameters(model)` → total params, trainable params
- Verify: full fine-tune = ~149M, LoRA R=16 = ~29.1M trainable (Table 6)

---

## Milestone 4 — CKC Loss, Training Loop & Continual Learning

---

### 4.1 Implement standard CLIP loss (Eq. 6)

- **File**: `c_clip/losses/clip_loss.py`
- `CLIPLoss(temperature)`:
  - Input: `z_v` (B, d), `z_c` (B, d) — normalized features
  - Compute `logits_per_image = z_v @ z_c.T / τ`
  - Compute `logits_per_text = z_c @ z_v.T / τ`
  - Labels = `torch.arange(B)` (diagonal is positive)
  - Loss = `(cross_entropy(logits_per_image, labels) + cross_entropy(logits_per_text, labels)) / 2`
  - Temperature τ is learnable (initialized from CLIP's `logit_scale`)

### 4.2 Implement CKC loss (Eq. 5)

- **File**: `c_clip/losses/ckc_loss.py`
- `CKCLoss(temperature)`:
  - Input: `h_new` (2N, d) — concatenated projected features `[h_ψ(f(v)), h_ψ(g(c))]`, L2-normalized
  - Input: `z_old` (2N, d) — concatenated old features `[f_old(v), g_old(c)]`, L2-normalized
  - Compute symmetric contrastive loss between `h_new` and `z_old`
  - Positive pair: `h_new[i]` ↔ `z_old[i]` (same sample, same modality position)
  - Negatives: all other `z_old[j]` for j ≠ i
  - Loss = `-1/(2N) * Σ [log(exp(h_i^T z_i / τ) / Σ_j exp(h_i^T z_j / τ)) + log(exp(z_i^T h_i / τ) / Σ_j exp(z_i^T h_j / τ))]`

### 4.3 Implement total loss combination

- **File**: `c_clip/losses/__init__.py`
- `TotalLoss`:
  - `L_total = L_CLIP + L_CKC`  (both equally weighted, no explicit lambda)
  - For the first task (no old model): `L_total = L_CLIP` only

### 4.4 Stage-wise optimizer configuration

- **File**: `c_clip/training/optimizer.py`
- `build_optimizer(model, dataset_name)`:
  - Optimizer: AdamW, weight_decay=0.2, β1=0.9, β2=0.99
  - **COCO-specific**: text encoder LR = 80× image encoder LR
    - Image encoder base LR = 5e-7
    - Text encoder LR = 4e-5
  - **Flickr30K**: base LR = 1e-5, text = 10× image
    - Image encoder LR = 1e-5
    - Text encoder LR = 1e-4
  - **Other datasets (Pet → Sketch)**: base LR = 3e-5, text = 10× image
    - Image encoder LR = 3e-5
    - Text encoder LR = 3e-4
  - Projector parameters use the text encoder LR
  - Create 3 param groups: `[vision_lora, text_lora, projector]`

### 4.5 Learning rate scheduler

- **File**: `c_clip/training/scheduler.py`
- Cosine decay schedule with linear warmup
- Warmup: 5 epochs
- Total: 40 epochs per task
- Initial LR = 1e-6 (during warmup, ramp from 1e-6 to target LR)

### 4.6 Single-task training function

- **File**: `c_clip/training/trainer.py`
- `train_one_task(model, train_loader, task_index, config)`:
  - Build optimizer (4.4)
  - Build scheduler (4.5)
  - For each epoch (1..40):
    - For each batch:
      - Forward pass through new model → z_v_new, z_c_new, h_v_new, h_c_new
      - If not first task: forward pass through old model → z_v_old, z_c_old
      - Compute L_CLIP(z_v_new, z_c_new)
      - If not first task: compute L_CKC(h_new, z_old)
      - Total loss = L_CLIP + L_CKC
      - Backprop & optimizer step
    - Log: epoch loss, LR, GPU memory

### 4.7 Post-task merge and reset

- **File**: `c_clip/training/trainer.py`
- `end_of_task(model)`:
  1. Merge LoRA into backbone with α=0.5: `merge_lora(model, alpha=0.5)`
  2. Snapshot merged model as old model: `model.snapshot_old_model()`
  3. Re-inject fresh LoRA layers: `reset_lora(model)`
  4. Save checkpoint

### 4.8 Continual training orchestrator

- **File**: `c_clip/training/trainer.py`
- `continual_train(model, config)`:
  - Task order: `[flickr30k, coco, pet, lexica, simpsons, wikiart, kream, sketch]`
  - For each task t in 0..7:
    - Load train DataLoader for task t
    - `train_one_task(model, loader, t, config)`
    - `end_of_task(model)`
    - Run `run_full_evaluation(model, stage_index=t+1)`
    - Log all metrics, save checkpoint

### 4.9 Checkpointing utility

- **File**: `c_clip/utils/checkpointing.py`
- Save after each task: `checkpoint_t{task_idx}.pt`
- Contents: model state_dict, old_model state_dict, projector state_dict, optimizer state_dict, task index, all eval metrics so far
- Load from checkpoint: resume training from any task

### 4.10 Logging and metrics tracking

- **File**: `c_clip/utils/logging.py`
- Log to console + wandb (if available)
- Track: per-epoch loss, per-task eval metrics, PD values
- Generate formatted tables matching paper format (Tables 3, 4)

---

## Milestone 5 — Full Training & Result Verification

### 5.1 Main training script

- **File**: `scripts/run_cclip.py`
- Parse config from `configs/default.yaml`
- Instantiate `CCLIPModel`
- Run `continual_train()`
- Print final results table

### 5.2 Full evaluation script

- **File**: `scripts/evaluate.py`
- Load a checkpoint
- Run `run_full_evaluation()`
- Compare with Table 3 (retrieval) and Table 4 (zero-shot classification)

### 5.3 Target metrics to reproduce

Paper's final numbers after training all 8 tasks (Table 3, ViT-B/16):

| Dataset | I2T R@1 | T2I R@1 |
|---------|---------|---------|
| flickr30k | 84.40 | 73.74 |
| COCO | 56.92 | 42.82 |
| pet | 19.73 | 17.91 |
| lexica | 42.65 | 41.47 |
| simpsons | 25.43 | 24.32 |
| wikiart | 45.89 | 45.27 |
| kream | 42.07 | 43.57 |
| sketch | 9.55 | 14.67 |
| **average** | **40.83** | **37.97** |

Zero-shot after all 8 tasks:
- ImageNet: 60.31% (PD = 7.42)
- CIFAR-100: 61.58% (PD = 5.29)

---

## Open Questions

> [!IMPORTANT]
> **GPU availability**: The paper trains on 8× NVIDIA 4090 GPUs with batch size 1024. What GPU resources do you have? We may need to use gradient accumulation to simulate large batches.

> [!IMPORTANT]
> **Dataset sourcing**: Some datasets (Lexica, Kream, WikiArt with captions) may not have straightforward downloads. Should we use the exact same HuggingFace sources as the official code, or find alternatives?

> [!WARNING]
> **Projector MLP architecture**: The paper mentions projector $h_ψ$ but doesn't give explicit layer dimensions. The official code should clarify this. Should we check the official repo in detail first?

> [!NOTE]
> **Training time estimate**: 40 epochs × 8 tasks. On a single GPU with smaller batch size, this could take multiple days. Are you okay with potentially long training runs?

---

## Verification Plan

### Automated Tests
1. **Data smoke test**: Load 1 batch from all 15 datasets, verify tensor shapes
2. **Baseline validation**: CLIP ViT-B/16 zero-shot ImageNet = 67.73% ± 0.5%
3. **Loss sanity check**: CKC loss converges on a small subset (100 samples)
4. **LoRA merge correctness**: Check that `merge → re-inject → forward` produces different outputs than before merge
5. **Retrieval math test**: Manually construct a known similarity matrix and verify R@1 calculation

### Manual Verification
- Compare training loss curves with Figure 3 in the paper
- Compare final retrieval numbers with Table 3
- Compare zero-shot degradation trajectory with Table 4
- Inspect qualitative retrieval results
