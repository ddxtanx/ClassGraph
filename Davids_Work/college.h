#pragma once

#include <vector>
#include <cstring>
#include "department.h"


//////////////////////////////////////////////////////////
/*  A class that holds our Graph and related functions
*/
//////////////////////////////////////////////////////////

class College 
{
    public:
        College();  //default constructor
        College(std::vector<Course> courses); //constructor given department
        size();
        insertCourse(/* key */);
        insertPrereq(/* course1, course2, key*/)
        removeCourse(/*asdf*/);
        incidentEdges(/* course */):
        areAdjacent(/* course1, course2 */):

        origin(/* prereq (edge) */); //do we need these?
        destination(/* prereq (edge) */); 

        BFS(); //maybe iterator?
        find(/*asdf*/); //use iterator to locate certain course??
        
    private:

        std::vector<Course> _courses;   //holds VERTS (classes)
        std::vector<Course> _prereqs;   //holds EDGES (prerequisits)
}
