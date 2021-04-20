#pragma once

#include <vector>
#include <cstring>
#include "department.h"


class College 
{
    public:
        College();  //default constructor
        College(const char* departmentFileName); //constructor given department
        BFS(); //maybe iterator?

        class Iterator : std::iterator<std::forward_iterator_tag, Point> 
        {
            public:
                Iterator();
                //Iterator(ImageTraversal * traversal, Point startPoint, const PNG * png, double tolerance);
                Iterator(Node startPoint);
                Iterator & operator++();
                Point operator*();
                bool operator!=(const Iterator &other);
                bool isDone() const;
            private:
                ImageTraversal * _traversal;
                Point _current;
                std::vector<bool> temp;
                std::vector< std::vector<bool> > _visited;
                const PNG * _png;
                HSLAPixel _startPxl;
                double _tol;
                bool _done;
        }
    private:
        virtual Iterator begin() = 0;

        virtual Iterator end() = 0;

        virtual void add(const Point & t) = 0;

        virtual Point pop() = 0;

        virtual Point peek() const = 0;

        virtual bool empty() const = 0;
}
