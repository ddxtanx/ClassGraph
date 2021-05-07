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
      Vertex*& operator*();
      bool operator!=(const Iterator &other);
      bool isDone() const;

      void add(const Vertex * vert);                         //iterator helpers
      Vertex* pop();
      Vertex* peek() const;
      bool empty() const;


    private:
      //pointer to BFS? i dont think necessary because not virtual
      //current vertex copy
      //std::vector<bool> temp;
      BFS * traversal_;
      Vertex * curr_;
      std::vector<bool> visited_;
      const Graph * graph_;
      bool done_;
      std::queue<const Vertex *> q_;     //queue for nodes to visit
  };

    BFS(const Graph * graph, Vertex * startPoint);    //traversal constructor

    Iterator begin();                                             //return iterator
    Iterator end();


private:
  //vars used for iterator
  const Graph * graph_;              //pointer to const graph data
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
*/