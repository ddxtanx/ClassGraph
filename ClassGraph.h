#pragma once
#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Vertex.h"
#include <string>
#include <vector>

class ClassGraph : public Graph{
    public:
        ClassGraph();
        ~ClassGraph();
    private:
        std::vector<Vertex*> vertexMap_;
        Vertex getOrCreateVertex(std::string courseName);
};