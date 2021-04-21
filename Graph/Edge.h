#pragma once
#include "Vertex.h"
class Edge{
    public:
        Edge();                                                      //constructors
        Edge(Vertex* from, Vertex* to);
        Edge(Vertex* from, Vertex* to, double weight);

        Vertex* getFrom();           //getter and setter functions
        Vertex* getTo();
        double getWeight();
        void setFrom(Vertex* newFrom);
        void setTo(Vertex* newTo);
        void setWeight(double newWeight);

        bool isValidEdge(); //checks to see if from and too point places

    private:
        Vertex* from_;       //edge data
        Vertex* to_;
        double weight_;
};