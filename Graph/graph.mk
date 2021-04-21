CXX = clang++
LD = clang++
GRAPH_DIR = Graph
GRAPH_OBJS_DIR = .objs/$(GRAPH_DIR)
OBJS_DIR += $(GRAPH_OBJS_DIR)

DEPFILE_FLAGS = -MMD -MP
DEPS = $(GraphDir)/Vertex.h $(GraphDir)/Edge.h $(GraphDir)/Graph.h
# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

# Flags for compile:
CXXFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c

# Flags for linking:
LDFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -lc++abi
GRAPH_OBJS =Edge Graph Vertex
NAMES=$(patsubst %, %.o, $(GRAPH_OBJS))
GRAPH_DIR_OBJS = $(patsubst %, $(GRAPH_DIR)/%.o, $(GRAPH_OBJS))
OBJS += $(GRAPH_DIR_OBJS)












