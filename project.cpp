#include <iostream>
#include "dataConvert.h"
#include "Davids_Work/BFS.h"
#include "Graph/Graph.h"
#include "ClassGraph.h"
#include "LGD/LGD.h"
#include "utils.h"


using namespace std;
std::string filename = "./Courses-and-prereqs/AllPrereqs.dat";


/**  /////////////////////////////////////////////////////////////////////////////////////////////////////
     * Main file used to interface with final project
     * 
     * @param arg0 -- No command line args runs ALL UIUC COURSES        formatted like:
     * @param arg1 -- Path to .dat file to use for graph data,          formatted like: ./project ./Courses-and-prereqs/CS_courses.dat    
     * @param arg2 -- String of a course to draw the prerequisits of,   formatted like: ./project ./Courses-and-prereqs/CS_courses.dat "CS 225"
     * 
     * @return     -- Command line information along with PNG output into ./Output_PNGs
     */  /////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  //Handles command line inputs
  string inputStr;
  string outputStr;
  Vertex* inputVert;
  if(argc == 2){
    filename = argv[1];
    inputStr = "";
  }
  if(argc == 3){
    filename = argv[1];
    inputStr = argv[2];
  }
  if(argc == 4){
    filename = argv[1];
    inputStr = argv[2];
    outputStr = argv[3];
  }






  ClassGraph g(filename);
  std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
  Vertex* start = g.getStart();
  Vertex* end = g.getEnd();



  //BFS TEST CODE//////////////////////////////////////////////////////////////////////////////////////////
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
  
  //BETWEENESS CENTRALITY TEST CODE////////////////////////////////////////////////////////////////////////

  g.initLayers();
  g.generateBetweennessCentrality(true, false);
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



  //LAYERED GRAPH DRAWING CODE/////////////////////////////////////////////////////////////////////////

  
  LGD gLGD(&g,start);
  if(inputStr != ""){
    inputVert = g.getVertexByName(inputStr);
  } else{
    inputVert = g.getStart();
  }
  Image output;

  if (inputStr != "yeet")
  {
    std::cout << "Running drawgraph from " << *inputVert << std::endl;
    output = gLGD.drawGraph(inputVert);
  }
  else
  {
    std::cout << "Running drawgraph from START" << std::endl;
    output = gLGD.drawGraph();
  }

  std::cout << "Writing to File" << std::endl;

  output.writeToFile("Outputs/Layered_Graph_Drawing.png");




  return 0;
}