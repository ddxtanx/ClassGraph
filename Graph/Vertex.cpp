#include "Vertex.h"
#include "../utils.h"
#include <string>
#include <vector>
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
    adjacentVertices_.insert(adjacentVertices_.end(), to);
}

std::vector<Vertex*> Vertex::getVerticesPointedTo(){
    return adjacentVertices_;
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