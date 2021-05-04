#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
Graph::Matrix<T>::Matrix(){
    rows_ = 0;
    cols_ = 0;
}

template <typename T>
Graph::Matrix<T>::Matrix(int rows, int cols){
    rows_ = rows;
    cols_ = cols;

    matrix_.resize(rows_ * cols_ + 1);
}

template <typename T>
int Graph::Matrix<T>::getCoordinate(int row, int col) const{
    return row*rows_ + col;
}

template <typename T>
void Graph::Matrix<T>::resizeMatrix(int rows, int cols){
    unsigned long rowLong = (unsigned long) rows;
    unsigned long colLong = (unsigned long) cols;
    unsigned long row_Long = (unsigned long) rows_;
    unsigned long col_Long = (unsigned long) cols_;
    if(rowLong*colLong > row_Long*col_Long){
        matrix_.resize(rowLong*colLong + 1);
        rows_ = rows;
        cols_ = cols;
    }
    
}

template <typename T>
T Graph::Matrix<T>::getVal(int row, int col) const{
    if(getCoordinate(row,col) < getCoordinate(rows_,cols_)){
        return matrix_[getCoordinate(row, col)];
    } else{
        std::cout << "Bad access at (" << row << "," << col << ") Coordinate: " << getCoordinate(row,col) << std::endl;
        return T();
    }
}

template <typename T>
void Graph::Matrix<T>::setVal(int row, int col, T val){
    if(getCoordinate(row,col) < getCoordinate(rows_,cols_)){
        matrix_[getCoordinate(row, col)] = val;
    } else{
        std::cout << "Bad access at (" << row << "," << col << ") Coordinate: " << getCoordinate(row,col) << std::endl;
        return;
    }
}

template <typename T>
std::pair<int, int> Graph::Matrix<T>::getDims() const{
    return {rows_, cols_};
}
Graph::Graph(){
}

Graph::Graph(std::vector<Vertex> vertices){
    vertices_.assign(vertices.begin(), vertices.end());

    size_t numVerts = vertices_.size();
    resizeAdjMatrix(numVerts);
}

Graph::Graph(std::vector<Vertex> vertices, std::vector<Edge> edges){
    vertices_.assign(vertices.begin(), vertices.end());
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

size_t Graph::getVerticiesSize() const
{
    return vertices_.size();
}
size_t Graph::getEdgesSize() const
{
    return edges_.size();
}

bool Graph::vertexInGraph(Vertex v) const{
    return std::count(vertices_.begin(), vertices_.end(), v);
}

double Graph::getWeightBetweenVertices(Vertex from, Vertex to) const{
    if(!vertexInGraph(from) || !vertexInGraph(to)){
        return -1;
    }
    size_t fromIndex = from.getId();
    size_t toIndex = to.getId();
    return (adjacencyMatrix_.getVal(fromIndex, toIndex));
}

double Graph::getWeightBetweenVertices(Edge e) const{
    if(!e.isValidEdge()){
        return -1;
    }
    return getWeightBetweenVertices(*e.getFrom(), *e.getTo());
}

void Graph::resizeAdjMatrix(size_t size){ //might need to alter this, might cause problems on resize
    std::pair<int,int> curDims = adjacencyMatrix_.getDims();
    if(curDims.first < (int)size || curDims.second < (int)size){
        adjacencyMatrix_.resizeMatrix(size, size);
    }
}
void Graph::addVertex(Vertex v){
    vertices_.insert(vertices_.end(), v);
    size_t newVertsSize = vertices_.size();
    resizeAdjMatrix(newVertsSize);
}

void Graph::addEdge(Edge e){
    if(!e.isValidEdge()){
        return;
    }
    edges_.push_back(e);
    Vertex from = *e.getFrom();
    Vertex to = *e.getTo();

    size_t fromIndex = from.getId();
    size_t toIndex = to.getId();
    if(adjacencyMatrix_.getVal(fromIndex, toIndex) != 0){
        return;
    }
    from.connectTo(e.getTo());
    double weight = e.getWeight();

    adjacencyMatrix_.setVal(fromIndex,toIndex,weight);
}

void Graph::addEdge(Vertex& from, Vertex& to, double weight){
    size_t fromIndex = from.getId();
    size_t toIndex = to.getId();

    if(adjacencyMatrix_.getVal(fromIndex,toIndex) != 0){
        return;
    }
    from.connectTo(&to);

    adjacencyMatrix_.setVal(fromIndex,toIndex,weight);

    Edge e(&from, &to, weight);
    edges_.push_back(e);
}