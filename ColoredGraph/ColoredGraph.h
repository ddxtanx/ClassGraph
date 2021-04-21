#pragma once
#include "ColoredVertex.h"
#include "ColoredEdge.h"
#include <vector>
class ColoredGraph{
    public:
        ColoredGraph();
        ColoredGraph(std::vector<ColoredVertex> vertices);
        ColoredGraph(std::vector<ColoredEdge> edges);
        ColoredGraph(std::vector<ColoredVertex> vertices, std::vector<ColoredEdge>);
        std::vector<ColoredVertex> getVertices();
        std::vector<ColoredEdge> getEdges();
        double getWeightBetweenVector(ColoredVertex from, ColoredVertex to);

        ColoredGraph* minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);
    private:
        std::vector<ColoredVertex> vertices_;
        std::vector<ColoredEdge> edges_;
        
        std::vector<std::vector<double>> adjacencyMatrix_;
};