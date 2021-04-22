#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
Graph::Graph(){
    Vertex start("Start");
    start_ = start;
    vertices_.insert(vertices_.end(), start_);
}

Graph::Graph(std::vector<Vertex> vertices){
    Vertex start("Start");
    start_ = start;
    vertices_.assign(vertices.begin(), vertices.end());
    vertices_.insert(vertices_.begin(), start_);

    size_t numVerts = vertices_.size();
    resizeAdjMatrix(numVerts);
}

Graph::Graph(std::vector<Vertex> vertices, std::vector<Edge> edges){
    Vertex start("Start");
    start_ = start;
    vertices_.assign(vertices.begin(), vertices.end());
    vertices_.insert(vertices_.begin(), start_);
    size_t numVerts = vertices_.size();
    resizeAdjMatrix(numVerts);
    for(Edge e : edges_){
        addEdge(e);
    }
}

std::vector<Vertex> & Graph::getVertices()
{
    return vertices_;
}
std::vector<Edge> & Graph::getEdges()
{
    return edges_;
}

Vertex& Graph::getStart(){
    return start_;
}

size_t Graph::getVerticiesSize()
{
    return vertices_.size();
}
size_t Graph::getEdgesSize()
{
    return edges_.size();
}

bool Graph::vertexInGraph(Vertex v){
    return std::count(vertices_.begin(), vertices_.end(), v);
}

double Graph::getWeightBetweenVertices(Vertex from, Vertex to){
    if(!vertexInGraph(from) || !vertexInGraph(to)){
        return -1;
    }
    size_t fromIndex = from.getId();
    size_t toIndex = to.getId();
    return adjacencyMatrix_[fromIndex][toIndex];    
}

double Graph::getWeightBetweenVertices(Edge e){
    if(!e.isValidEdge()){
        return -1;
    }
    return getWeightBetweenVertices(*e.getFrom(), *e.getTo());
}

void Graph::resizeAdjMatrix(size_t size){
    if(adjacencyMatrix_.size() < size){
        adjacencyMatrix_.resize(size+1);
    }
    for(auto row : adjacencyMatrix_){
        if(row.size() < size){
            row.resize(size+1);
        }
    }
}
void Graph::addVertex(Vertex v){
    vertices_.insert(vertices_.end(), v);
    size_t newVertsSize = vertices_.size();
    resizeAdjMatrix(newVertsSize);
}

void Graph:: addEdge(Edge e){
    if(!e.isValidEdge()){
        return;
    }
    edges_.insert(edges_.end(), e);
    Vertex from = *e.getFrom();
    Vertex to = *e.getTo();
    double weight = e.getWeight();

    size_t fromIndex = from.getId();
    size_t toIndex = to.getId();

    adjacencyMatrix_[fromIndex][toIndex] = weight;
}