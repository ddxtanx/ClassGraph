#include <iostream>
#include "dataConvert.h"
#include "Davids_Work/BFS.h"
#include "Graph/Graph.h"
#include "ClassGraph.h"
#include "utils.h"
using namespace std;
std::string filename = "./Courses-and-prereqs/AllPrereqs.dat";
int main(int argc, char** argv)
{
  if(argc == 2){
    filename = argv[1];
  }
  ClassGraph g(filename);
  g.makeAcyclic();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "#####################################   Welcome to the danger zone  --  (Start of main)   ######################################" << std::endl;
  std::cout<< "# of verts in graph: " << g.getVertices().size()<<std::endl;

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "------------------------------------------------------" << std::endl;

  std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
  //Vertex* start = g.getStart();
  /*
    std::cout << "Printing First 15 vertexes in graph obj: " << std::endl;
    int count = 0;
    for (std::vector<Vertex*>::iterator it = verts.begin(); it != verts.end(); ++it)
    {
      std::cout << count << " " << **it << std::endl;
      ++count;
      if (count == 15)
        break;

    }
  */

  Vertex* start = g.getStart();

  BFS traversal(&g, start);                    //create traversal, start at vert 0
  for (auto it = traversal.begin(); it != traversal.end(); ++it)
  {
    Vertex v = **it;
    std::cout << "Prerequisites of " << v << ": ";
    for(Vertex* vp : v.getVerticesPointedTo()){
      std::cout << *vp << ", ";
    } 
    std::cout << std::endl;
  }
  return 0;


}