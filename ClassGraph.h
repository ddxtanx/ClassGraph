#pragma once
#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Vertex.h"
#include <string>
#include <vector>

class ClassGraph : public Graph{
    public:
        ClassGraph(const std::string fileName);
        ~ClassGraph();

        Vertex*& getStart();
    private:
        std::vector<Vertex*> vertexMap_;
        Vertex* getOrCreateVertex(std::string courseName);
        Vertex* start_;
};