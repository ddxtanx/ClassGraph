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
    bool fromEq = false;
    bool toEq = false;
    if(from_ == nullptr){
        fromEq = other.from_ == nullptr;
    } else if(other.from_ == nullptr){
        return false;
    } else{
        fromEq = from_ -> getId() == other.from_->getId();
    }
    if(to_ == nullptr){
        toEq = other.to_ == nullptr;
    } else if(other.to_ == nullptr){
        return false;
    } else{
        toEq = to_ -> getId() == other.to_ -> getId();
    }
    return fromEq && toEq;
}

bool Edge::operator<(const Edge& other) const{
    if(from_ == nullptr){
        return true;
    } else if(from_ != nullptr && other.from_ == nullptr){
        return false;
    } else if(from_ -> getId() == other.from_ -> getId() && to_ == nullptr){
        return true;
    } else if(from_ -> getId() == (other.from_) -> getId() && to_ != nullptr && other.to_ == nullptr){
        return false;
    }
    return (from_ -> getId() < other.from_->getId()|| (from_ -> getId() == other.from_ -> getId() && to_ -> getId() < other.to_ -> getId()));
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

