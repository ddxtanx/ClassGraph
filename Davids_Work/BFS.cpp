#include "BFS.h"
#include <queue>



//Iterator stuff
  //std::vector<bool> visited;
  //std::queue<* Vertex> q;
  //Vertex * current;

BFS::Iterator::Iterator()
: current(NULL)
{
    //nothing
}

BFS::Iterator::Iterator(Vertex * start, Graph * g)
: current(start)
{
    visited.resize(g->getVerticesSize()); //init visited to size of graph
    //q.push(current);
}

BFS::Iterator & BFS::Iterator::operator++()
{

    visited[current->getId()] = 1;      //mark current as visited

    std::vector<Vertex*> adj = current->getVerticesPointedTo();                     //returns all vertecies that current points to
    for (Vertex* v : adj)    //push all valid adjacent verts
    {
        if(v != nullptr){
            q.push(v);
        }
    }

    while(!q.empty())       //Until q is empty or point is not visited
    {
        current = q.front();
        q.pop();

        if (current != nullptr && !visited[current->getId()]) //if current has not been visited
            break;                      //  return current basically
    }

    if (q.empty() && current != nullptr && visited[current->getId()])      //check if end of traversal
        current = NULL;

    return *this;
}

BFS::Iterator& BFS::Iterator::operator++(int){
    auto cur = this;
    operator++();
    return *cur;
}

Vertex * BFS::Iterator::operator*() const
{
    return current;   //returns reference to vertex in graph
}
bool BFS::Iterator::operator!=(const BFS::Iterator &other) const
{
    return isDone() != other.isDone();       //compares current vertexes, returns results
}


bool BFS::Iterator::isDone() const
{
    if(current != NULL)
        return false;
    else
        return true;
}




//traversal container stuff
  //Graph * graph_;
  //Vertex * root_;
  //std::vector<Vertex> * verts_;  //private data from graph
  //std::vector<Edge> * edges_;

BFS::BFS()  //null
: graph_(NULL), root_(NULL),verts_(NULL),edges_(NULL)
{
    //nothing
}
BFS::BFS(Graph & g, Vertex & v) //reference
: graph_(&g), root_(&v)
{
    verts_ = &(g.getVertices());
    edges_ = &(g.getEdges());
}
BFS::BFS(Graph * g, Vertex * v) //pointer
: graph_(g), root_(v)
{
    verts_ = &(g->getVertices());
    edges_ = &(g->getEdges());
}
BFS::Iterator BFS::begin()
{
    return BFS::Iterator(root_, graph_);
}
BFS::Iterator BFS::end()
{
    return BFS::Iterator(); //null
}

/*
Graph();                                                                         //constructors
        Graph(std::vector<Vertex> vertices);
        Graph(std::vector<Vertex> vertices, std::vector<Edge> edges);

        std::vector<Vertex> & getVertices();   //used for printing and whole graph representation
        std::vector<Edge> & getEdges();
        Vertex& getStart();

        bool vertexInGraph(Vertex v) const;
        
        double getWeightBetweenVertices(Vertex from, Vertex to) const;                    //used in algorithms
        double getWeightBetweenVertices(Edge edge) const;

        //ColoredGraph minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticesSize() const;
        size_t getEdgesSize() const;
        //iterator for BFS?

        void addVertex(Vertex vert);
        void addEdge(Vertex from, Vertex to, double weight);
        void addEdge(Edge e);
*/




















