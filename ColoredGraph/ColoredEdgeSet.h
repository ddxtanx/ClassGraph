#pragma once
#include <vector>
#include "ColoredEdge.h"
class ColoredEdgeSet{
    public:
        ColoredEdgeSet();                                   //constructors
        ColoredEdgeSet(ColoredEdge edge);
        ColoredEdgeSet(std::vector<ColoredEdge> edges);

        std::vector<ColoredEdge> getEdges();                //getter

        bool contains(ColoredEdge e);
        void addEdge(ColoredEdge e);
        void removeEdge(ColoredEdge e)


    private:
        std::vector<ColoredEdge> edges_;
};