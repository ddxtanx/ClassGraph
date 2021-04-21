#include "Graph.h"
#include <iostream>
#include <vector>
Graph::Graph(){
    start_ = new Vertex("Start");
}

Graph::Graph(std::vector<Vertex*> vertices){
    vertices_.assign(vertices.begin(), vertices.end());
    size_t numVerts = vertices_.size();
    adjacencyMatrix_.resize(vertices_.size());
    for(size_t i = 0; i<numVerts; i++){
        adjacencyMatrix_[i].resize(numVerts);
    }
}

Graph::Graph(std::vector<Vertex*> vertices, std::vector<Edge*> edges){
    vertices_.assign(vertices.begin(), vertices.end());
    edges_.assign(edges.begin(), edges.end());
    size_t numVerts = vertices_.size();
    adjacencyMatrix_.resize(vertices_.size());
    for(size_t i = 0; i<numVerts; i++){
        adjacencyMatrix_[i].resize(numVerts);
    }
    for(Edge* e : edges_){
        Vertex* from = e -> getFrom();
        Vertex* to = e -> getTo();
        double weight = e -> getWeight();

        size_t fromIndex = from -> getId();
        size_t toIndex = to -> getId();

        adjacencyMatrix_[fromIndex][toIndex] = weight;
    }
}