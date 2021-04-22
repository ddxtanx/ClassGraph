GRAPH_DIR = Graph
GRAPH_OBJS_DIR = .objs/$(GRAPH_DIR)

GRAPH_OBJS =Edge Graph Vertex
GRAPH_DIR_OBJS = $(patsubst %, $(GRAPH_DIR)/%.o, $(GRAPH_OBJS))
OBJS += $(GRAPH_DIR_OBJS)












