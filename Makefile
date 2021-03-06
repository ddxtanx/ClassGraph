OBJS_DIR = .objs
EXE = project
TEST=test

EXE_OBJ=project.o
OBJS=project.o utils.o ClassGraph.o dataConvert.o

CXXFLAGS += -g -ggdb -pg
LDFLAGS += -lprofiler -ltcmalloc
include Graph/graph.mk
include Davids_Work/david.mk
include LGD/LGD.mk
include Stickers/Stickers.mk
include cs225/make/cs225.mk
clean:
	find .objs -type f -name "*.[d|o]" -exec rm {} \;
	rm -f project
	rm -f test
