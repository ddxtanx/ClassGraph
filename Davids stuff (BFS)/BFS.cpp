#include "BFS.h"


//////////////////////////////////// Iterator /////////////////////////////////////////////


BFS::Iterator::Iterator()                                                                                       //done
: graph_(NULL), curr_(NULL), done_(true)
{
    //nothing
}
BFS::Iterator::Iterator(const Graph * graph, Vertex * startPoint, BFS * traversal)                //done
: traversal_(traversal), curr_(startPoint), graph_(graph), _done(false)
{
    int size = graph->getVerticiesSize();
    for ( int i = 0; i < size, ++i)
    {
        visited_.push_back(0);  //init visited list
    }
}

BFS::Iterator & BFS::Iterator::operator++() //used mp_traversals as structure                                   //done?
{                                                                                                       
    visited_[curr_->getID()] = 1;                                                            
    traversal_->add(curr_);             //push current and neighbors(current)
    for (auto it = curr_->adjacentVertecies.begin(); it != curr_->adjacentVertecies.end(); ++it)
    {
        //if vert is unvisited, add(*it)
        if (visited[*it->getID()])
            continue;
        else
            traversal_->add(*it);
  }

  do {                                  //Until q_ is empty or vert is not visited, point = q_.pop()
    if (traversal_->empty())            //Until S is empty
        break;                          //end of traversal
    curr_ = traversal_->pop();          //point = q_.pop()  
  } while(visited_[curr_->getID()]);                  //loop if point is not visited and valid    

    if (traversal_->empty())
        done_ = true;
    return *this;

}
Vertex & BFS::Iterator::operator*()                                                                      //done
{
    return curr_;
}
bool BFS::Iterator::operator!=(const Iterator &other)                                                           //done
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
        if (curr_->id_ == *other->id_)
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

Iterator BFS::begin()                                                                                           //done?
{
    return Iterator::Iterator(graph_, root_, this);
}
Iterator BFS::end()                                                                                             //done
{
    return Iterator::Iterator();
}

void BFS::add(const Vertex & vert)                                                                       //done
{
    q_.push(vert); 
}
Vertex BFS::pop()                                                                                        //done
{
    Vertex temp = q_.front();
    q_.pop();
    return temp;
}
Vertex BFS::peek() const                                                                                 //done
{
    return q_.front();
}
bool BFS::empty() const                                                                                         //done
{
    return q_.empty();
}