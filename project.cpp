#include <iostream>
#include "dataConvert.h"
#include "Davids_Work/BFS.h"
#include "Graph/Graph.h"
#include "ClassGraph.h"
using namespace std;

int main()
{
  ClassGraph g;
  std::cout<<g.getVertices().size()<<std::endl;

  
  std::vector<Vertex> & verts = g.getVertices();  //get reference to vertices
  Vertex start = verts[0];
  std::cout << start << std::endl;
  BFS traversal(&g, &verts[0]);                    //create traversal, start at vert 0

  //for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
  //{
  //  std::cout << **it << std::endl;
  //}
  return 0;
}