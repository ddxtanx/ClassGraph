#pragma once

#include "course.h"
#include <vector>

//////////////////////////////////////////////////////////
/*  Iterator class to traverse the graph?? idk yet WIP
*/
//////////////////////////////////////////////////////////


class Iterator : std::iterator<std::forward_iterator_tag, Point> 
{
  public:
    Iterator();
    Iterator(ImageTraversal * traversal, Point startPoint, const PNG * png, double tolerance);

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    //bool isDone() const;
  private:
    //ImageTraversal * _traversal;
    //Point _current;
    //std::vector<bool> temp;
    //std::vector< std::vector<bool> > _visited;
    //const PNG * _png;
    //HSLAPixel _startPxl;
    //double _tol;
    //bool _done;
};

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

private: