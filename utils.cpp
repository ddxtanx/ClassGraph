#include <string>
#include "utils.h"
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "dataConvert.h"

std::unordered_map<std::string, int> Utils::deptNumMap;
std::string Utils::courseRegexStr;
bool Utils::mapInitialized = false;
bool Utils::deptsInitialized = false;
std::vector<std::string> Utils::depts;
int Utils::numDepts = -1;

void Utils::initializeDepts(std::string fileName){
    deptsInitialized = true;
    depts = DataConvert::getDepartments(fileName);
    numDepts = depts.size();
    courseRegexStr = "(";
    int n = 0;
    for(std::string deptName : depts){
        courseRegexStr += deptName;
        if(n != numDepts - 1){
            courseRegexStr += "|";
        }
        n++;
    }
    courseRegexStr += ")";
}
int Utils::getDeptNum(std::string department){
    if(!deptsInitialized){
        std::cout << "Need to initialize depts first!" << std::endl;
        return -1;
    }
    if(!mapInitialized){
        int i = 0;
        for(std::string dept: depts){
            deptNumMap[dept] = i;
            i++;
        }
        mapInitialized = true;
    }
    return deptNumMap[department];
}
int Utils::hashCourseName(std::string courseName){
    if(!deptsInitialized){
        std::cout << "Need to initialize depts first!" << std::endl;
        return -1;
    }
    std::regex classRegex(courseRegexStr + " ([0-7][0-9]{2})");
    std::smatch matches;
    if(std::regex_match(courseName, matches, classRegex)){
        std::string dept = matches[1].str();
        std::string numStr = matches[2].str();
        int num = std::stoi(numStr);
        int thousandsMult = getDeptNum(dept);
        return thousandsMult*800+num;
    }
    std::cout << "Class does not fit regex: " << courseName << std::endl; 
    return -1;
}

const std::string whiteSpaces( " \f\n\r\t\v" );


void Utils::trimRight(std::string& str)
{
   std::string::size_type pos = str.find_last_not_of( whiteSpaces );
   str.erase( pos + 1 );    
}


void Utils::trimLeft( std::string& str)
{
   std::string::size_type pos = str.find_first_not_of( whiteSpaces );
   str.erase( 0, pos );
}


void Utils::trim( std::string& str)
{
   trimRight(str);
   trimLeft(str);
} 