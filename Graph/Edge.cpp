#include "Edge.h"
Edge::Edge(){
    from_ = nullptr;
    to_ = nullptr;
    weight_ = 0;
}

Edge::Edge(Vertex* from, Vertex* to){
    from_ = from;
    to_ = to;
    weight_ = 0;
}

Edge::Edge(Vertex* from, Vertex* to, double weight){
    from_ = from;
    to_ = to;
    weight_ = weight;
}

Vertex* Edge::getFrom(){
    return from_;
}

Vertex* Edge::getTo(){
    return to_;
}

double Edge::getWeight(){
    return weight_;
}

void Edge::setFrom(Vertex* newFrom){
    from_ = newFrom;
}

void Edge::setTo(Vertex* newTo){
    to_ = newTo;
}

void Edge::setWeight(double newWeight){
    weight_ = newWeight;
}

