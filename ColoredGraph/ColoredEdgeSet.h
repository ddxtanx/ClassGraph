#pragma once
#include <vector>
#include "ColoredEdge.h"
class ColoredEdgeSet{
    public:
        ColoredEdgeSet();
        ColoredEdgeSet(std::vector<ColoredEdge> edges);
        std::vector<ColoredEdge> getEdges();
        bool contains(ColoredEdge e);
        void addEdge(ColoredEdge e);
    private:
        std::vector<ColoredEdge> edges_;
};