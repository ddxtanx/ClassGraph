STICKER_DIR = Stickers
STICKER_OBJS_DIR = .objs/$(STICKER_DIR)

STICKER_OBJS =Image StickerSheet
STICKER_DIR_OBJS = $(patsubst %, $(STICKER_DIR)/%.o, $(STICKER_OBJS))
OBJS += $(STICKER_DIR_OBJS)
