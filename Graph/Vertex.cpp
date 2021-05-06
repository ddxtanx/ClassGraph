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
}

Vertex::Vertex(std::string name){
    name_ = name;
    id_ = count;
    count++;
}

void Vertex::connectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    size_t id = to -> getId();
    if(id >= adjacencies_.size()){
        adjacencies_.resize(2*id);
    }
    adjacencies_[id] = to;
}

void Vertex::disconnectTo(Vertex* to){
    if(to == nullptr){
        return;
    }
    size_t id = to -> getId();
    if(id >= adjacencies_.size()){
        adjacencies_.resize(2*id);
    }
    adjacencies_[id] = nullptr;
}

std::vector<Vertex*> Vertex::getVerticesPointedTo(){
    std::vector<Vertex*> nonNulls;
    for(Vertex* vp : adjacencies_){
        if(vp != nullptr){
            nonNulls.push_back(vp);
        }
    }
    return nonNulls;
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
