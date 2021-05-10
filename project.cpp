#include <iostream>
#include "dataConvert.h"
#include "Davids_Work/BFS.h"
#include "Graph/Graph.h"
#include "ClassGraph.h"
#include "LGD/LGD.h"
#include "utils.h"
#include "SpanningTree/SpanningTree.h"


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
  Vertex* start = g.getStart();
  Vertex* end = g.getEnd();

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

  g.generateBetweennessCentrality(true);
  Vertex mostImportantVertex;
  double maxScore = std::numeric_limits<double>::min();
  for(std::pair<Vertex, double> betwCent : *g.getBetweennessCentrality()){
    Vertex v = betwCent.first;
    double score = betwCent.second;
    std::cout << "The betweenness centrality of " << v << " is " << score << std::endl;

    if(score > maxScore){
      maxScore = score;
      mostImportantVertex = v;
    }
  }

  std::cout << "The most central vertex in the graph is " << mostImportantVertex << " with a centrality of " << maxScore << std::endl;
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Testing draw Vertex" << std::endl;

  std::cout << "Creating LGD obj with graph g and START" << std::endl;
  LGD l(&g, start);
  std::cout << "Calling DrawGraph" << std::endl;
  Image output = l.drawGraph();
  std::cout << "Writing to File" << std::endl;
  output.writeToFile("Output_PNGs/myImage.png");

  
  return 0;
}