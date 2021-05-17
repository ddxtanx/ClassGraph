#include "dataConvert.h"
#include <iostream>
#include <fstream>
using std::ifstream;

#include <cstring>
#include <vector>
#include <regex>
#include "utils.h"

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = ",";

std::vector<std::vector<std::string>> DataConvert::getData(const std::string fileName)
{
  std::vector<std::vector<std::string>> tokens;
  ifstream fin(fileName);
  if (!fin.good())
  { 
    std::cout<<"FAILED TO OPEN FILE"<<std::endl;
    return tokens; // exit if file not found
  }
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    std::string line = "";
    std::getline(fin, line, '\n');
    Utils::trim(line);

    // parse the line into blank-delimited tokens

    // Vector to store memory addresses of the tokens in buf
    std::vector<std::string> token;
    std::regex lineRegex("(([A-Z]{2,9} [0-9]{3})(,|$|\n){1})");
    std::smatch matches;
    while(std::regex_search(line, matches, lineRegex)){
      std::string courseName = matches[2].str(); // matches goes {"Course Name," "Course Name,", "Coursename", ","}
      token.push_back(courseName);
      line = matches.suffix().str();
    }
    //Parse the line.
    /*char* first=strtok(buf, DELIMITER);//Get first token
    token.push_back(std::string(first));
    if(first)
    {
        for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        char* currTok = (strtok(0, DELIMITER)); // subsequent tokens
        if (!currTok) break; // no more tokens
        token.push_back(std::string(currTok));//If token is not null, add it to the token vector
      }
    }*/
    tokens.push_back(token); //Push the current token to the vector of tokens.
  }
  return tokens;
}

std::vector<std::string> DataConvert::getDepartments(const std::string filename){
  std::vector<std::string> deptNames;
  ifstream fin;
  fin.open(filename);
  if(!fin.good()){
    return deptNames;
  }
  std::string currentCourse = "";
  while(!fin.eof()){
    std::string line;
    std::getline(fin, line);
    Utils::trim(line);

    std::regex courseRegex("[A-Z]{2,9}");
    std::smatch matches;
    if(std::regex_search(line, matches, courseRegex)){
      std::string courseName = matches[0].str();
      if(courseName.empty()){
        continue;
      }
      if(courseName != currentCourse){
        deptNames.push_back(courseName); 
        currentCourse = courseName;
      }
    }
  }
  return deptNames;
}