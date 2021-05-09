#pragma once
#include "../Graph/Graph.h"
#include "../Graph/Edge.h"
#include "../Graph/Vertex.h"
#include "../ClassGraph.h"
#include <string>
#include <vector>
#include "../Davids_Work/BFS.h"

class SpanningTree : public Graph{
    public:
        SpanningTree(ClassGraph& other);
        Vertex*& getStart();
        Vertex*& getEnd();
        void makeAcyclic();
    private:
        Vertex* TreeStart;
        std::vector<Edge> Edges;
        std::vector<Vertex*> vertices;
};