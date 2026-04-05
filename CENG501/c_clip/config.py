# C-CLIP: Multimodal Continual Learning — Centralized Configuration

# === Model ===
MODEL_NAME = "openai/clip-vit-base-patch16"
IMAGE_SIZE = 224
MAX_TEXT_LEN = 77
FEATURE_DIM = 512  # CLIP ViT-B/16 feature dimension

# === Training ===
BATCH_SIZE = 1024  # Reduce if GPU memory is limited
EPOCHS = 40
WARMUP_EPOCHS = 5
RANDOM_SEED = 42
NUM_WORKERS = 4

# === LoRA ===
LORA_RANK = 16
LORA_ALPHA = 32  # 2×R
LORA_DROPOUT = 0.1
MERGE_ALPHA = 0.5

# === Optimizer ===
WEIGHT_DECAY = 0.2
BETA1 = 0.9
BETA2 = 0.99

# === Learning Rates (per dataset) ===
# Format: (image_encoder_lr, text_encoder_lr)
LR_CONFIG = {
    "flickr30k": (1e-5, 1e-4),       # text = 10× image
    "coco": (5e-7, 4e-5),             # text = 80× image
    "pets": (3e-5, 3e-4),             # text = 10× image
    "lexica": (3e-5, 3e-4),           # text = 10× image
    "simpsons": (3e-5, 3e-4),         # text = 10× image
    "wikiart": (3e-5, 3e-4),          # text = 10× image
    "kream": (3e-5, 3e-4),            # text = 10× image
    "sketch": (3e-5, 3e-4),           # text = 10× image
}

# === Task Order ===
TASK_ORDER = [
    "flickr30k", "coco", "pets", "lexica",
    "simpsons", "wikiart", "kream", "sketch"
]

# === Paths ===
DATA_DIR = "./data"
CHECKPOINT_DIR = "./checkpoints"
LOG_DIR = "./logs"

# === Projector ===
PROJECTOR_HIDDEN_DIM = 512
PROJECTOR_OUTPUT_DIM = 512
