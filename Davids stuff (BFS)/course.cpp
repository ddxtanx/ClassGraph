#include <cstring>

#include "course.h"



Course::Course()                //default constructor, name = null
: name('\0')
{}

Course::Course(std::string name)    
: name(name)
{}

