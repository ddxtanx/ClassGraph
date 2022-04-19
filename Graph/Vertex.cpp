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
    regenTo_ = true;
    regenFrom_ = true;
}

Vertex::Vertex(std::string name){
    name_ = name;
    id_ = count;
    count++;
    numPointsTo = 0;
    numPointsFrom = 0;
    layer_=0;
    regenTo_ = true;
    regenFrom_ = true;
}

void Vertex::connectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    if(!pointsToMap_[to]){
        pointsToMap_[to] = true;
        numPointsTo++;
        regenTo_ = true;
        regenFrom_ = true;
    }
}

void Vertex::disconnectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    if(pointsToMap_[to]){
        pointsToMap_[to] = false;
        numPointsTo --;
        regenTo_ = true;
        regenFrom_ = true;
    }
}

void Vertex::connectFrom(Vertex* from){
    if(from == nullptr){
        return;
    }
    if(!pointsFromMap_[from]){
        pointsFromMap_[from] = true;
        regenTo_ = true;
        regenFrom_ = true;
        numPointsFrom++;
    }
}

void Vertex::disconnectFrom(Vertex* from){
    if(from == nullptr){
        return;
    }
    if(pointsFromMap_[from]){
        pointsFromMap_[from] = false;
        numPointsFrom --;
        regenTo_ = true;
        regenFrom_ = true;
    }
}

std::vector<Vertex*> & Vertex::getVerticesPointedTo(){
    if(regenTo_){
        pointsTo_.clear();
        for(auto pair : pointsToMap_){
            if(pair.second && pair.first != nullptr){
                pointsTo_.push_back(pair.first);
            }
        }
    }
    regenTo_ = false;
    return pointsTo_;
}

std::vector<Vertex*> & Vertex::getVerticesPointedFrom(){
    if(regenFrom_){
        pointsFrom_.clear();
        for(auto pair : pointsFromMap_){
            if(pair.second && pair.first != nullptr){
                pointsFrom_.push_back(pair.first);
            }
        }
    }
    regenFrom_ = false;
    return pointsFrom_;
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

bool Vertex::operator<(const Vertex& v) const{
    return (id_ < v.id_);
}

void Vertex::setId(size_t id){
    id_ = id;
}

void Vertex::setCountNum(size_t c){
    count = c;
}
