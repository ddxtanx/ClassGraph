#include "BFS.h"
#include <queue>



//iterator stuff
  //std::vector<bool> visited;
  //std::queue<* Vertex> q;
  //Vertex * current;

BFS::iterator::iterator()
: current(NULL)
{
    //nothing
}
BFS::iterator::iterator(Vertex * start)
: current(start)
{
    visited.resize(graph_->getVerticiesSize()); //init visited to size of graph
    q.push(start);                              //start q
}
BFS::iterator & BFS::iterator::operator++()
{
    
//set root as visited
//push root to q

//while (!q.empty())
//      v = q.dequeue()
//      if (v == target)
//          return
//      push all valid surrounding cells (aka if edge is valid and not visited)
//          mark visited
//          q.enque(node)

}
Vertex * BFS::iterator::operator*()
{
    return current;   //returns reference to vertex in graph
}
bool BFS::iterator::operator!=(const iterator &other)
{
    return current != other;       //compares current vertexes, returns results
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
BFS::iterator BFS::begin()
{
    return BFS::iterator(   &(graph_->getStart())   );
}
BFS::iterator BFS::end()
{
    return BFS::iterator(); //null
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
        size_t getVerticiesSize() const;
        size_t getEdgesSize() const;
        //iterator for BFS?

        void addVertex(Vertex vert);
        void addEdge(Vertex from, Vertex to, double weight);
        void addEdge(Edge e);
*/




















//old code
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*
//////////////////////////////////// Iterator /////////////////////////////////////////////


BFS::Iterator::Iterator()                                                                                       //done
: curr_(NULL), graph_(NULL), done_(true)
{
    //nothing
}
BFS::Iterator::Iterator(const Graph * graph, Vertex * startPoint, BFS * traversal)                //done
: traversal_(traversal), curr_(startPoint), graph_(graph)
{
    done_ = false;
    int size = graph->getVerticiesSize();
    for ( int i = 0; i < size; ++i)
    {
        visited_.push_back(0);  //init visited list
    }
}

BFS::Iterator & BFS::Iterator::operator++() //used mp_traversals as structure                                   //done?
{                                                                                                       
    visited_[curr_->getId()] = 1;                                                            
    add(curr_);             //push current and neighbors(current)
    auto neighbors = curr_->getVerticesPointedTo();
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        //if vert is unvisited, add(*it)
        if (visited_[(*it) -> getId()])
            continue;
        else
            add(*it);
  }

  do {                                  //Until q_ is empty or vert is not visited, point = q_.pop()
    if (empty())            //Until S is empty
        break;                          //end of traversal
    curr_ = pop();          //point = q_.pop()  
  } while(visited_[curr_->getId()]);                  //loop if point is not visited and valid    

    if (empty())
        done_ = true;
    return *this;

}
Vertex *& BFS::Iterator::operator*()                                                                      //done
{
    return curr_;
}
bool BFS::Iterator::operator!=(const BFS::Iterator &other)                                                           //done
{
    //if empty, return false (aka if at end/Null, return false)
    bool thisEmpty = false; 
    bool otherEmpty = false;
    if (isDone()) { thisEmpty = true; }
    if (other.isDone()) { otherEmpty = true; }

    if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
    //else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
    else if (!thisEmpty && !otherEmpty)
    {
        Vertex* otherCurr = other.peek();
        if (curr_->getId() == otherCurr->getId())
            return false;               //values equal
        else
            return true;                //values present but unequal
    }
    else
        return true; // one is empty while the other is not, return true
}

bool BFS::Iterator::isDone() const                                                                              //done
{
    return done_;
}

/////////////////////////////////// Traversal /////////////////////////////////////////////

BFS::BFS(const Graph * graph, Vertex * startPoint)                                                //done
: graph_(graph), root_(startPoint)
{}

BFS::Iterator BFS::begin()                                                                                           //done?
{
    //Iterator(const Graph * graph, Vertex * startPoint, BFS * traversal)
    return BFS::Iterator(graph_, root_, this);
}
BFS::Iterator BFS::end()                                                                                             //done
{
    return BFS::Iterator();
}

void BFS::Iterator::add(const Vertex * vert)                                                                       //done
{
    q_.push(vert); 
}
Vertex* BFS::Iterator::pop()                                                                                        //done
{
    Vertex temp = q_.front();
    q_.pop();
    return temp;
}
Vertex* BFS::Iterator::peek() const                                                                                 //done
{
    return q_.front();
}
bool BFS::Iterator::empty() const                                                                                         //done
{
    return q_.empty();
}

*/