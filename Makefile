OBJS_DIR = .objs
EXE = project
TEST=test

EXE_OBJ=project.o
OBJS=project.o utils.o ClassGraph.o dataConvert.o

include Graph/graph.mk
include Davids_Work/david.mk
include cs225/make/cs225.mk