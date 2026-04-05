# C-CLIP: Multimodal Continual Learning

Clean implementation of **C-CLIP** (ICLR 2025) — a method for continual learning in vision-language models.

## Overview

C-CLIP addresses catastrophic forgetting in CLIP when learning from sequential multimodal tasks. It combines:
- **LoRA** (Low-Rank Adaptation) for parameter-efficient fine-tuning
- **CKC Loss** (Contrastive Knowledge Consolidation) to preserve knowledge from previous tasks
- **Projector MLP** to map features into a shared space for knowledge distillation

## Project Structure

```
c_clip/
├── config.py            # All hyperparams & paths
├── data/                # Dataset loaders (15 datasets)
├── model/               # CLIP wrapper, LoRA, projector, C-CLIP orchestrator
├── losses/              # CLIP loss + CKC loss
├── evaluation/          # Retrieval & classification metrics
├── training/            # Training loop, optimizer, scheduler
└── utils/               # Logging & checkpointing
scripts/                 # Entry points for downloading, training, evaluating
configs/                 # YAML configuration files
```

## Setup

```bash
python3 -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
```

## Quick Start

1. **Download datasets**: `python scripts/download_datasets.py`
2. **Prepare splits**: `python scripts/prepare_splits.py`
3. **Validate baseline**: `python scripts/run_baseline.py`
4. **Train C-CLIP**: `python scripts/run_cclip.py`
5. **Evaluate**: `python scripts/evaluate.py --checkpoint checkpoints/checkpoint_t7.pt`

## Target Metrics

After training all 8 tasks (ViT-B/16):

| Metric | Target |
|--------|--------|
| Avg I2T R@1 | 40.83 |
| Avg T2I R@1 | 37.97 |
| ImageNet Accuracy | 60.31% (PD = 7.42) |
| CIFAR-100 Accuracy | 61.58% (PD = 5.29) |

## Reference

Paper: [C-CLIP: Continual Learning for Vision-Language Models](https://openreview.net/forum?id=...) (ICLR 2025)
Official Repo: https://github.com/SmallPigPeppa/C-CLIP
