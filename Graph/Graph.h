#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
class Graph{
    public:     
        Graph();                                                                         //constructors
        Graph(std::vector<Vertex> vertices);
        //ColoredGraph(std::vector<ColoredEdge> edges);                                         //cannot have edges without vertexes...
        Graph(std::vector<Vertex> vertices, std::vector<Edge> edges);

        std::vector<Vertex> getVertices();   //used for printing and whole graph representation
        std::vector<Edge> getEdges();


        double getWeightBetweenVector(Vertex from, Vertex to);                    //used in algorithms
        double getWeightBetweenVector(Edge edge);

        //ColoredGraph* minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticiesSize();
        size_t getEdgesSize();
        //iterator for BFS?


    private:
        std::vector<Vertex> vertices_;
        std::vector<Edge> edges_;
        //ColoredVertex* start_;                //not necessary except for traversals
        
        std::vector<std::vector<double>> adjacencyMatrix_;
};