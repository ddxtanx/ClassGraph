#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
class Graph{
    public:     
        Graph();                                                                         //constructors
        Graph(std::vector<Vertex*> vertices);
        //ColoredGraph(std::vector<ColoredEdge> edges);                                         //cannot have edges without vertexes...
        Graph(std::vector<Vertex*> vertices, std::vector<Edge*> edges);

<<<<<<< HEAD
        std::vector<Vertex> & getVertices();   //used for printing and whole graph representation
        std::vector<Edge> & getEdges();
=======
        std::vector<Vertex*> getVertices();   //used for printing and whole graph representation
        std::vector<Edge*> getEdges();
>>>>>>> 0d05876366565760e60bd28580161d1be4a7aed1


        double getWeightBetweenVector(Vertex* from, Vertex* to);                    //used in algorithms
        double getWeightBetweenVector(Edge* edge);

        //ColoredGraph* minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticiesSize();
        size_t getEdgesSize();
        //iterator for BFS?


    private:
        std::vector<Vertex*> vertices_;
        std::vector<Edge*> edges_;
        Vertex* start_;                
        
        std::vector<std::vector<double>> adjacencyMatrix_;
};