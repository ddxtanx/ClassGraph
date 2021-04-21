#pragma once

#include "../Graph/Graph.h"
#include <iterator>
#include <vector>
#include <list>
#include <queue>

//////////////////////////////////////////////////////////
/*  Iterator container for traversing graphs
*/
//////////////////////////////////////////////////////////

class BFS
{
public:
  class Iterator 
  : std::iterator<std::forward_iterator_tag, Vertex> 
  {
    public:
      Iterator();
      Iterator(const Graph * graph, Vertex * startPoint, BFS * traversal);

      Iterator & operator++();
      Vertex & operator*();
      bool operator!=(const Iterator &other);
      bool isDone() const;

    private:
      //pointer to BFS? i dont think necessary because not virtual
      //current vertex copy
      //std::vector<bool> temp;
      BFS * traversal_;
      Vertex * curr_;
      std::vector<bool> visited_;
      Graph * graph_;
      bool done_;
  };

    BFS(const Graph & graph, Vertex & startPoint);    //traversal constructor

    Iterator begin();                                             //return iterator
    Iterator end();

    void add(const Vertex & vert);                         //iterator helpers
    Vertex pop();
    Vertex peek() const;
    bool empty() const;

private:
  //vars used for iterator
  Graph & graph_;              //pointer to const graph data
  Vertex * root_;              //start point
  
  std::queue<Vertex *> q_;     //queue for nodes to visit
  //  +++++++++++++++                 //visited node graph

}