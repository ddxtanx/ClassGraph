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

  //Vertex* start = g.getStart();
  Vertex* start = verts[0];

  BFS traversal(&g, start);                    //create traversal, start at vert 0
  std::cout << "Classes that require " << start->getName() << ":" << std::endl;
  BFS::Iterator it = traversal.begin();
  ++it;
  for (; it != traversal.end(); ++it)
  {
    std::cout << **it << std::endl; 
  }
  return 0;


}