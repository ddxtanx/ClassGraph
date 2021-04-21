#pragma once

#include "ColoredVertex.h"
class ColoredEdge{
    public:
        ColoredEdge();

        ColoredEdge(ColoredVertex* from, ColoredVertex* to);

        ColoredEdge(ColoredVertex* from, ColoredVertex* to, double weight);

        ColoredVertex* getFrom();

        ColoredVertex* getTo();
        
        double getWeight();
    private:
        ColoredVertex* from_;
        ColoredVertex* to_;
        double weight_;
};