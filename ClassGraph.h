#pragma once
#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Vertex.h"
#include <string>
#include <vector>

class ClassGraph : public Graph{
    public:
        ClassGraph(const std::string fileName);
        ClassGraph(const ClassGraph& ot);

        Vertex*& getStart();
        Vertex*& getEnd();
        
        ClassGraph& operator=(const ClassGraph& ot);

        Vertex*& getVertexByName(std::string name);

        void makeAcyclic();
    private:
        std::vector<Vertex*> vertexMap_;
        Vertex* getOrCreateVertex(std::string courseName);

        Vertex* start_;
        Vertex* end_;
};