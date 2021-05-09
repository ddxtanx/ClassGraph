LGD_DIR = LGD
LGD_OBJS_DIR = .objs/$(LGD_DIR)

LGD_OBJS = LGD
LGD_DIR_OBJS = $(patsubst %, $(LGD_DIR)/%.o, $(LGD_OBJS))
OBJS += $(LGD_DIR_OBJS)
