#pragma once

#include "../Graph/Graph.h"
#include <iterator>
#include <vector>
#include <list>
#include <queue>

class BFS
{
  public:
  class Iterator 
  : std::iterator<std::forward_iterator_tag, Vertex *>
  {
    public:
    Iterator();
    Iterator(Vertex * start, Graph * g);

    Iterator & operator++();
    Iterator & operator++(int);
    Vertex * operator*() const;
    bool operator!=(const Iterator &other) const;

    bool isDone() const;

    private:
    std::vector<bool> visited;    
    std::queue<Vertex*> q;
    Vertex * current;             //is NULL when finished
  };

  BFS();  //constructors
  BFS(Graph & g, Vertex & v);   //create by reference for easy use
  BFS(Graph * g, Vertex * v);   //create by pointer for flexibility

  BFS::Iterator begin();        //returns iterator to start node
  BFS::Iterator end();
  


  private:
  Graph * graph_;                 //pointers to object to search
  Vertex * root_;                 //pointer to start node
  std::vector<Vertex*> * verts_;  //private data from graph
  std::vector<Edge> * edges_;
  
};


