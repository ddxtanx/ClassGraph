#include "Graph.h"
#include "Vertex.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <queue>

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
        if(vp == nullptr){
            continue;
        }
        Edge e(v, vp);
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
    to.connectFrom(e.getFrom());

    adjacencyMatrix_.setVal(fromIndex,toIndex,1);
}

void Graph::addEdge(Vertex* from, Vertex* to){
    if(from == nullptr || to == nullptr){
        return;
    }
    size_t fromIndex = from -> getId();
    size_t toIndex = to -> getId();

    if(adjacencyMatrix_.getVal(fromIndex,toIndex) != 0){
        return;
    }
    from -> connectTo(to);
    to -> connectFrom(from);

    adjacencyMatrix_.setVal(fromIndex,toIndex,1);

    Edge e(from, to);
    edges_.push_back(e);
}

void Graph::makeAcyclic(Vertex* source, bool backwards, Vertex* necessaryVertex){
    if(!vertexInGraph(source)){
        return;
    }
    std::vector<Edge> edges;
    std::vector<int> levelIndex;
    std::vector<bool> seenBefore;
    seenBefore.resize(getVerticiesSize());
    levelIndex.assign(getVerticiesSize(), -1);
    levelIndex[source -> getId()] = 0;
    std::stack<Edge> st;
    Edge firstE(source, source);
    st.push(firstE);
    while(!st.empty()){
        Edge e = st.top();
        st.pop();

        Vertex* from = e.getFrom();
        Vertex* to = e.getTo();
        size_t fromId = from -> getId();
        size_t toId = to -> getId();
        seenBefore[fromId] = true;
        seenBefore[toId] = true;
        if(from != to){
            edges.push_back(e);
            if(backwards){
                int prevLevel = levelIndex[toId];
                levelIndex[fromId] = prevLevel+1;
            } else{
                int prevLevel = levelIndex[fromId];
                levelIndex[toId] = prevLevel+1;
            }
        }

        Vertex* nextVertex;
        size_t nextId;
        std::vector<Vertex*> nextVertices;
        if(backwards){
            nextVertex = from;
            nextId = from -> getId();
            nextVertices = from -> getVerticesPointedFrom();
        } else{
            nextVertex = to;
            nextId = to -> getId();
            nextVertices = to -> getVerticesPointedTo();
        }
        for(Vertex* vp : nextVertices){
            size_t adjId = vp -> getId();
            if((vp != necessaryVertex && seenBefore[adjId] && levelIndex[adjId] < levelIndex[nextId]) || vp == nextVertex){
                if(backwards){
                    vp -> disconnectTo(nextVertex);
                    nextVertex -> disconnectFrom(vp);
                    adjacencyMatrix_.setVal(adjId, nextId, 0);
                } else{
                    vp -> disconnectFrom(nextVertex);
                    nextVertex -> disconnectTo(vp);
                    adjacencyMatrix_.setVal(nextId, adjId, 0);
                }
                continue;
            }
            if(backwards){
                Edge nextE(vp, nextVertex);
                st.push(nextE);
            } else{
                Edge nextE(nextVertex, vp);
                st.push(nextE);
            }
        }
    }
    edges_ = edges;
    for(Vertex* v : vertices_){
        if(v != necessaryVertex && v -> getNumPointedFrom() == 0){
            addEdge(necessaryVertex, v);
        }
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
            Edge e(newVertex, newVertexN);
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

void Graph::generateBetweennessCentrality(bool backwards){ //Assumes unweighted
    if(!betweennessCentrality_.empty()){
        return;
    }
    std::unordered_map<Vertex, double> betwCent;
    size_t numVertices = getVerticiesSize();
    Matrix<size_t> shortestPathMatrix(numVertices, numVertices);  //value at (row,col) represents shortest path from row vert to col vert
    for(size_t i = 0; i < numVertices; i++){
        shortestPathMatrix.setVal(i,i,i);
    }
    for(Vertex* v : vertices_){
        std::stack<Vertex*> stack1;
        std::vector<size_t> shortestPathNum(numVertices, 0);
        shortestPathNum[v -> getId()] = 1;
        std::vector<int> minDistance(numVertices, -1);
        minDistance[v -> getId()] = 0;
        std::queue<Vertex*> distQueue;
        distQueue.push(v);
        while(!distQueue.empty()){
            Vertex* vn = distQueue.front();
            distQueue.pop();
            stack1.push(vn);
            double distToVertex = minDistance[vn -> getId()];
            auto nextVertices = backwards ? vn -> getVerticesPointedFrom() : vn -> getVerticesPointedTo();
            for(Vertex* neighbor : nextVertices){
                int& curDistance = minDistance[neighbor -> getId()];
                if(curDistance == -1){
                    distQueue.push(neighbor);
                    curDistance = distToVertex + 1;
                }
                if(curDistance == distToVertex + 1){
                    shortestPathMatrix.setVal(v -> getId(), neighbor -> getId(), vn -> getId());
                    shortestPathNum[neighbor -> getId()] += shortestPathNum[vn -> getId()];
                }
            }
        }
        std::vector<double> dependencies(numVertices, 0);
        while(!stack1.empty()){
            Vertex* vn = stack1.top();
            stack1.pop();
            size_t vertId = vn -> getId();
            size_t nextId = vertId;
            do{
                nextId = shortestPathMatrix.getVal(v -> getId(), nextId);
                if(vertId != nextId){
                    dependencies[nextId] += (double(shortestPathNum[nextId]))/(double(shortestPathNum[vertId]))*(1 + dependencies[vertId]);
                }
            }while(nextId != v -> getId());
            if(vn != v){
                betwCent[*vn] += dependencies[vertId];
            }
        }
    }
    betweennessCentrality_ = betwCent;
}

double Graph::getBetweennessCentrality(Vertex* source){
    if(betweennessCentrality_.empty()){
        std::cout << "Betweenness centrality has not been generated yet" << std::endl;
        return -1;
    }
    return betweennessCentrality_[*source];
}

std::unordered_map<Vertex, double>* Graph::getBetweennessCentrality(){
    return &betweennessCentrality_;
}