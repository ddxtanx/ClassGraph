#pragma once

#include "../ColoredGraph/ColoredGraph.h"
#include <iterator>
#include <vector>
#include <list>
#include <queue>

//////////////////////////////////////////////////////////
/*  Iterator class to traverse the graph?? idk yet WIP
*/
//////////////////////////////////////////////////////////

class BFS
{
public:
  class Iterator 
  : std::iterator<std::forward_iterator_tag, ColoredVertex> 
  {
    public:
      Iterator();
      Iterator(const ColoredGraph * graph, ColoredVertex * startPoint, BFS * traversal);

      Iterator & operator++();
      ColoredVertex & operator*();
      bool operator!=(const Iterator &other);
      bool isDone() const;

    private:
      //pointer to BFS? i dont think necessary because not virtual
      //current vertex copy
      //std::vector<bool> temp;
      BFS * traversal_;
      ColoredVertex * curr_;
      std::vector<bool> visited_;
      ColoredGraph * graph_;
      bool done_;
  };

    BFS(const ColoredGraph & graph, ColoredVertex & startPoint);    //traversal constructor

    Iterator begin();                                             //return iterator
    Iterator end();

    void add(const ColoredVertex & vert);                         //iterator helpers
    ColoredVertex pop();
    ColoredVertex peek() const;
    bool empty() const;

private:
  //vars used for iterator
  ColoredGraph & graph_;              //pointer to const graph data
  ColoredVertex * root_;              //start point
  
  std::queue<ColoredVertex *> q_;     //queue for nodes to visit
  //  +++++++++++++++                 //visited node graph

}