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
  Graph g;
  std::vector<Vertex> ECE_Vertices;
  std::vector<Vertex> CS_Vertices;
  std::vector<Vertex> PHYS_Vertices;
  std::vector<Vertex> MATH_Vertices;
  for(unsigned i=0;i<ECE_data.size();i++)
  {
    std::vector<std::string> firstTok=ECE_data[i];
    ECE_Vertices.push_back(Vertex(firstTok[0]));
  }
  for(unsigned i=0;i<CS_data.size();i++)
  {
    std::vector<std::string> firstTok=CS_data[i];
    CS_Vertices.push_back(Vertex(firstTok[0]));
  }
  for(unsigned i=0;i<MATH_data.size();i++)
  {
    std::vector<std::string> firstTok=MATH_data[i];
    MATH_Vertices.push_back(Vertex(firstTok[0]));
  }
  for(unsigned i=0;i<PHYS_data.size();i++)
  {
    std::vector<std::string> firstTok=PHYS_data[i];
    PHYS_Vertices.push_back(Vertex(firstTok[0]));
  }
  std::cout<<CS_Vertices.size()<<" "<<ECE_Vertices.size()<<" "<<PHYS_Vertices.size()<<" "<<MATH_Vertices.size()<<std::endl;
  return 0;
}