#include "Vertex.h"
#include "../utils.h"
#include <string>
#include <vector>
#include <algorithm>
size_t Vertex::count = 0;
Vertex::Vertex(){
    name_ = "";
    id_ = count;
    count++;
    numPointsTo = 0;
    numPointsFrom = 0;
    layer_=0;
}

Vertex::Vertex(std::string name){
    name_ = name;
    id_ = count;
    count++;
    numPointsTo = 0;
    numPointsFrom = 0;
    layer_=0;
}

void Vertex::connectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    if(!pointsTo_[to]){
        pointsTo_[to] = true;
        numPointsTo++;
    }
}

void Vertex::disconnectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    if(pointsTo_[to]){
        pointsTo_[to] = false;
        numPointsTo --;
    }
}

void Vertex::connectFrom(Vertex* from){
    if(from == nullptr){
        return;
    }
    if(!pointsFrom_[from]){
        pointsFrom_[from] = true;
        numPointsFrom++;
    }
}

void Vertex::disconnectFrom(Vertex* from){
    if(from == nullptr){
        return;
    }
    if(pointsFrom_[from]){
        pointsFrom_[from] = false;
        numPointsFrom --;
    }
}

std::vector<Vertex*> Vertex::getVerticesPointedTo(){
    std::vector<Vertex*> nonNulls;
    for(auto pair : pointsTo_){
        if(pair.second){
            nonNulls.push_back(pair.first);
        }
    }
    return nonNulls;
}

std::vector<Vertex*> Vertex::getVerticesPointedFrom(){
    std::vector<Vertex*> nonNulls;
    for(auto pair : pointsFrom_){
        if(pair.second){
            nonNulls.push_back(pair.first);
        }
    }
    return nonNulls;
}


unsigned Vertex::getLayer() const{
    return layer_;
}

void Vertex::setLayer(unsigned layer){
    layer_=layer;
}

size_t Vertex::getNumPointedTo(){
    return numPointsTo;
}

size_t Vertex::getNumPointedFrom(){
    return numPointsFrom;
}

std::string Vertex::getName() const{
    return name_;
}

size_t Vertex::getId() const{
    return id_;
}

bool Vertex::operator==(const Vertex v) const{
    return (name_ == v.name_);
}

void Vertex::setId(size_t id){
    id_ = id;
}

void Vertex::setCountNum(size_t c){
    count = c;
}
