#pragma once

#include <cstring>

//////////////////////////////////////////////////////////
/*  A struct to act as vertexes, containing data about the
    course, such as a string name, and possibly a hash
    generator, or unique id, or any other data we want
*/
//////////////////////////////////////////////////////////


struct Course
{
    Course();
    Course(std::string name);

    std::string name = "No Name Given";
    unsigned int courseNumber = 0;
}

struct Prereq
{
    Prereq();
    Prereq(course & c1, course & c2);   //takes reference to two verts, makes edge between them

    course*
}

