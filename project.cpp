#include <iostream>
#include "dataConvert.cpp"
#include "Davids stuff (BFS)/BFS.h"
#include "Graph/Graph.h"
using namespace std;

int main()
{
  
  std::vector<std::vector<std::string>> CS_data=getData("Courses-and-prereqs/CS_courses.dat");
  std::vector<std::vector<std::string>> ECE_data=getData("Courses-and-prereqs/ECE_courses.dat");
  std::vector<std::vector<std::string>> MATH_data=getData("Courses-and-prereqs/MATH_courses.dat");
  std::vector<std::vector<std::string>> PHYS_data=getData("Courses-and-prereqs/PHYS_courses.dat");
  std::vector<Vertex> Vertices;
  for(unsigned i=0;i<ECE_data.size();i++)
  {
    std::vector<std::string> firstTok=ECE_data[i];
    Vertices.push_back(Vertex(firstTok[0]));
  }
  for(unsigned i=0;i<CS_data.size();i++)
  {
    std::vector<std::string> firstTok=CS_data[i];
    Vertices.push_back(Vertex(firstTok[0]));
  }
  for(unsigned i=0;i<MATH_data.size();i++)
  {
    std::vector<std::string> firstTok=MATH_data[i];
    Vertices.push_back(Vertex(firstTok[0]));
  }
  for(unsigned i=0;i<PHYS_data.size();i++)
  {
    std::vector<std::string> firstTok=PHYS_data[i];
    Vertices.push_back(Vertex(firstTok[0]));
  }
  Graph g(Vertices);
  std::cout<<Vertices.size()<<std::endl;
  return 0;
}