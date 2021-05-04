#include <iostream>
#include "dataConvert.h"
#include "Davids_Work/BFS.h"
#include "Graph/Graph.h"
#include "ClassGraph.h"
using namespace std;

int main()
{
  ClassGraph g;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "#####################################   Welcome to the danger zone  --  (Start of main)   ######################################" << std::endl;
  std::cout<< "# of verts in graph: " << g.getVertices().size()<<std::endl;

  std::vector<Vertex> & verts = g.getVertices();  //get reference to vertices
  Vertex start = verts[0];
  std::cout << "Printing First 10 vertexes in graph obj: " << std::endl;

  int count = 0;
  for (std::vector<Vertex>::iterator it = verts.begin(); it != verts.end(); ++it)
  {
    std::cout << *it << std::endl;
    ++count;
    if (count == 10)
      break;

  }



  BFS traversal(&g, &verts[2]);                    //create traversal, start at vert 0

  for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
  {
    std::cout << "test" << std::endl;
    std::cout << **it << std::endl;     //dereferences the iterator (which is *Vertex), 
                                        //then dereference that and use its std::out functionality
    std::cout << "test" << std::endl;   
  }
  return 0;


}