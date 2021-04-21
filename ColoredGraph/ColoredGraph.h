#pragma once
#include "ColoredVertex.h"
#include "ColoredEdge.h"
#include <vector>
class ColoredGraph{
    public:     
        ColoredGraph();                                                                         //constructors
        ColoredGraph(std::vector<ColoredVertex> vertices);
        //ColoredGraph(std::vector<ColoredEdge> edges);                                         //cannot have edges without vertexes...
        ColoredGraph(std::vector<ColoredVertex> vertices, std::vector<ColoredEdge> edges);

        std::vector<ColoredVertex> getVertices();   //used for printing and whole graph representation
        std::vector<ColoredEdge> getEdges();


        double getWeightBetweenVector(ColoredVertex from, ColoredVertex to);                    //used in algorithms
        double getWeightBetweenVector(ColoredEdge edge);

        ColoredGraph* minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticiesSize();
        size_t getEdgesSize();
        //iterator for BFS?


    private:
        std::vector<ColoredVertex> vertices_;
        std::vector<ColoredEdge> edges_;
        //ColoredVertex* start_;                //not necessary except for traversals
        
        std::vector<std::vector<double>> adjacencyMatrix_;
};