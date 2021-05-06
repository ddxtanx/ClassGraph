#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../FibonacciHeap/fiboqueue.h"

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

Graph::Graph(std::vector<Vertex*> vertices){
    vertices_.assign(vertices.begin(), vertices.end());

    size_t numVerts = vertices_.size();
    resizeAdjMatrix(numVerts);
}

Graph::Graph(std::vector<Vertex*> vertices, std::vector<Edge> edges){
    vertices_.assign(vertices.begin(), vertices.end());
    size_t numVerts = vertices_.size();
    resizeAdjMatrix(numVerts);
    for(Edge e : edges_){
        addEdge(e);
    }
}

std::vector<Vertex*> & Graph::getVertices() 
{
    return vertices_;
}
std::vector<Edge> & Graph::getEdges()
{
    return edges_;
}

std::vector<Edge> Graph::getEdgesFrom(Vertex* v) const{
    if(!vertexInGraph(v)){
        return {};
    }
    std::vector<Edge> edges;
    for(Vertex* vp : v -> getVerticesPointedTo()){
        double weight = getWeightBetweenVertices(*v, *vp);
        Edge e(v, vp, weight);
        edges.push_back(e);
    }
    return edges;
}

size_t Graph::getVerticiesSize() const
{
    return vertices_.size();
}
size_t Graph::getEdgesSize() const
{
    return edges_.size();
}

bool Graph::vertexInGraph(Vertex* v) const{
    return v -> getId() < getVerticiesSize();
}

double Graph::getWeightBetweenVertices(Vertex from, Vertex to) const{
    if(!vertexInGraph(&from) || !vertexInGraph(&to)){
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
void Graph::addVertex(Vertex* v){
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

void Graph::addEdge(Vertex* from, Vertex* to, double weight){
    if(from == nullptr || to == nullptr){
        return;
    }
    size_t fromIndex = from -> getId();
    size_t toIndex = to -> getId();

    if(adjacencyMatrix_.getVal(fromIndex,toIndex) != 0){
        return;
    }
    from -> connectTo(to);

    adjacencyMatrix_.setVal(fromIndex,toIndex,weight);

    Edge e(from, to, weight);
    edges_.push_back(e);
}

void Graph::makeAcyclic(Vertex* source){
    if(!vertexInGraph(source)){
        return;
    }
    std::vector<Edge> edges;
    std::vector<bool> vertexInMST;
    vertexInMST.resize(getVerticiesSize());
    Edge e(source, source, 0);
    FibQueue<Edge, std::less<Edge>> fq;
    fq.push(e);
    while(!fq.empty()){
        Edge e = fq.top();
        Vertex* end = e.getTo();
        vertexInMST[e.getFrom() -> getId()] = true;
        if(end != source){
            edges.push_back(e);
        }
        std::vector<Edge> pointedEdges = getEdgesFrom(end);
        for(Edge edge : pointedEdges){
            Vertex* from = edge.getFrom();
            Vertex* to = edge.getTo();
            if(vertexInMST[to -> getId()]){
                from->disconnectTo(to);
                adjacencyMatrix_.setVal(from -> getId(), to -> getId(), 0);
                continue;
            }
            fq.push(edge);
        }
        fq.pop();
    }
}

void Graph::clear(){
    for(Vertex* v : vertices_){
        if(v != nullptr){
            delete v;
            v = nullptr;
        }
    }
}

Graph::~Graph(){
    clear();
}

void Graph::copy(const Graph& other){
    std::vector<Edge> newEdges;
    std::vector<Vertex*> newVertices;
    newVertices.resize(other.getVerticiesSize());
    adjacencyMatrix_ = other.adjacencyMatrix_;

    for(Vertex* v : other.vertices_){
        size_t id = v -> getId();
        Vertex* newVertex;
        if(newVertices[id] == nullptr){
            newVertex = new Vertex(*v);
            newVertices[id] = newVertex;
        } else{
            newVertex = newVertices[id];
        }
        for(Vertex* vn : v->getVerticesPointedTo()){
            size_t idn = vn -> getId();
            Vertex* newVertexN;
            if(newVertices[idn] == nullptr){
                newVertexN = new Vertex(*vn);
                newVertices[idn] = newVertexN; 
            } else{
                newVertexN = newVertices[idn];
            }
            double weight = other.getWeightBetweenVertices(*v, *vn);
            Edge e(newVertex, newVertexN, weight);
            newEdges.push_back(e);
        }
    }
    vertices_ = newVertices;
    edges_ = newEdges;
}

Graph& Graph::operator=(const Graph& ot){
    if(&ot != this){
        clear();
    }
    copy(ot);
    return *this;
}

Graph::Graph(const Graph& ot){
    copy(ot);
}