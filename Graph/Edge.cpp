#include "Edge.h"
Edge::Edge(){
    from_ = nullptr;
    to_ = nullptr;
}

Edge::Edge(Vertex* from, Vertex* to){
    from_ = from;
    to_ = to;
}

bool Edge::operator==(const Edge& other) const{
    return (from_ == other.from_) && (to_ == other.to_);
}

Vertex* Edge::getFrom() const{
    return from_;
}

Vertex* Edge::getTo() const{
    return to_;
}

void Edge::setFrom(Vertex* newFrom){
    from_ = newFrom;
}

void Edge::setTo(Vertex* newTo){
    to_ = newTo;
}


bool Edge::isValidEdge() const{
    return from_ != nullptr && to_ != nullptr;
}

