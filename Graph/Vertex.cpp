#include "Vertex.h"
#include "../utils.h"
#include <string>
#include <vector>
#include <algorithm>
int Vertex::count = 0;
Vertex::Vertex(){
    name_ = "";
    id_ = count;
    count++;
    numPointsTo = 0;
    numPointsFrom = 0;
}

Vertex::Vertex(std::string name){
    name_ = name;
    id_ = count;
    count++;
    numPointsTo = 0;
    numPointsFrom = 0;
}

void Vertex::connectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    size_t id = to -> getId();
    if(id >= pointsTo_.size()){
        pointsTo_.resize(id+1);
    }
    if(pointsTo_[id] == nullptr){
        numPointsTo++;
    }
    pointsTo_[id] = to;
    
}

void Vertex::disconnectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    size_t id = to -> getId();
    if(id >= pointsTo_.size()){
        pointsTo_.resize(id+1);
    }
    if(pointsTo_[id] != nullptr){
        numPointsTo --;
    }
    pointsTo_[id] = nullptr;
}

void Vertex::connectFrom(Vertex* from){
    if(from == nullptr){
        return;
    }
    size_t id = from -> getId();
    if(id >= pointsFrom_.size()){
        pointsFrom_.resize(id+1);
    }
    if(pointsFrom_[id] == nullptr){
        numPointsFrom++;
    }
    pointsFrom_[id] = from;
    
}

void Vertex::disconnectFrom(Vertex* from){
    if(from == nullptr){
        return;
    }
    size_t id = from -> getId();
    if(id >= pointsFrom_.size()){
        pointsFrom_.resize(id+1);
    }
    if(pointsFrom_[id] != nullptr){
        numPointsFrom --;
    }
    pointsFrom_[id] = nullptr;
}

std::vector<Vertex*> Vertex::getVerticesPointedTo(){
    std::vector<Vertex*> nonNulls;
    for(Vertex* vp : pointsTo_){
        if(vp != nullptr){
            nonNulls.push_back(vp);
        }
    }
    return nonNulls;
}

std::vector<Vertex*> Vertex::getVerticesPointedFrom(){
    std::vector<Vertex*> nonNulls;
    for(Vertex* vp : pointsFrom_){
        if(vp != nullptr){
            nonNulls.push_back(vp);
        }
    }
    return nonNulls;
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

void Vertex::setId(int id){
    id_ = id;
}

void Vertex::setCountNum(int c){
    count = c;
}

int Vertex::getCountNum(){
    return count;
}
