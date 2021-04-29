#pragma once

#include <string>

class Utils{
    public:
        static int hashCourseName(std::string courseName);
        static void trimRight(std::string& str);
        static void trimLeft(std::string& str);
        static void trim(std::string& str);
        static int numDepts;
};