#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
class Graph{
    public:     
        Graph();                                                                         //constructors
        Graph(std::vector<Vertex> vertices);
        Graph(std::vector<Vertex> vertices, std::vector<Edge> edges);

        std::vector<Vertex> & getVertices();   //used for printing and whole graph representation
        std::vector<Edge> & getEdges();

        bool vertexInGraph(Vertex v);
        
        double getWeightBetweenVertices(Vertex from, Vertex to);                    //used in algorithms
        double getWeightBetweenVertices(Edge edge);

        //ColoredGraph minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticiesSize();
        size_t getEdgesSize();
        //iterator for BFS?

        void addVertex(Vertex vert);
        void addEdge(Vertex from, Vertex to, double weight);
        void addEdge(Edge e);


    private:
        std::vector<Vertex> vertices_;
        std::vector<Edge> edges_;
        Vertex start_;                
        
        std::vector<std::vector<double>> adjacencyMatrix_;

        void resizeAdjMatrix(size_t size);
};