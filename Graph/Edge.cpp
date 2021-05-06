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

bool Edge::operator<(const Edge& other) const{
    return weight_ < other.weight_;
}

bool Edge::operator==(const Edge& other) const{
    return (from_ == other.from_) && (to_ == other.to_) && (weight_ == other.weight_);
}

Vertex* Edge::getFrom() const{
    return from_;
}

Vertex* Edge::getTo() const{
    return to_;
}

double Edge::getWeight() const{
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

bool Edge::isValidEdge() const{
    return from_ != nullptr && to_ != nullptr;
}

