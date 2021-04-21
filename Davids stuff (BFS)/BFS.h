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

      void add(const Vertex & vert);                         //iterator helpers
      Vertex pop();
      Vertex peek() const;
      bool empty() const;


    private:
      //pointer to BFS? i dont think necessary because not virtual
      //current vertex copy
      //std::vector<bool> temp;
      BFS * traversal_;
      Vertex * curr_;
      std::vector<bool> visited_;
      Graph * graph_;
      bool done_;
      std::queue<Vertex *> q_;     //queue for nodes to visit
  };

    BFS(const Graph & graph, Vertex & startPoint);    //traversal constructor

    Iterator begin();                                             //return iterator
    Iterator end();


private:
  //vars used for iterator
  Graph & graph_;              //pointer to const graph data
  Vertex * root_;              //start point
  
  
  //  +++++++++++++++                 //visited node graph
  /////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

};