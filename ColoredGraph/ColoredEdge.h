#pragma once

#include "ColoredVertex.h"
class ColoredEdge{
    public:
        ColoredEdge();                                                      //constructors
        ColoredEdge(ColoredVertex* from, ColoredVertex* to);
        ColoredEdge(ColoredVertex* from, ColoredVertex* to, double weight);

        ColoredVertex* getFrom();           //getter and setter functions
        ColoredVertex* getTo();
        double getWeight();
        void setFrom();
        void setTo();
        void setWeight();

    private:
        ColoredVertex* from_;       //edge data
        ColoredVertex* to_;
        double weight_;
};