#include "Graph.h"
#include <iostream>
Graph::Graph(){
    std::cout << "Hi" << std::endl;
}





std::vector<Vertex> & Graph::getVertices()
{
    return vertices_;
}
std::vector<Edge> & Graph::getEdges()
{
    return edges_;
}

size_t Graph::getVerticiesSize()
{
    return vertices_.size();
}
size_t Graph::getEdgesSize()
{
    retrurn edges_.size();
}