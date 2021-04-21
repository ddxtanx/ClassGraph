#include <iostream>
#include "dataConvert.cpp"
#include "Davids stuff (BFS)/BFS.h"
using namespace std;

int main()
{
  std::vector<std::vector<std::vector<std::string>>> Departments;
  std::vector<std::vector<std::string>> CS_data=getData("Courses-and-prereqs/CS_courses.dat");
  Departments.push_back(CS_data);
  std::vector<std::vector<std::string>> ECE_data=getData("Courses-and-prereqs/ECE_courses.dat");
  Departments.push_back(ECE_data);
  std::vector<std::vector<std::string>> MATH_data=getData("Courses-and-prereqs/MATH_courses.dat");
  Departments.push_back(MATH_data);
  std::vector<std::vector<std::string>> PHYS_data=getData("Courses-and-prereqs/PHYS_courses.dat");
  Departments.push_back(PHYS_data);
  for(unsigned i=0;i<ECE_data.size();i++)
  {std::vector<std::string> firstTok=ECE_data[i];
  for (unsigned i = 0; i < firstTok.size(); i++)
    cout << "Token[" << i << "] = " << firstTok[i] << endl;
  cout << endl;
  }
  return 0;
}