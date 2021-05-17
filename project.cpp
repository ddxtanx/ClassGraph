#include <iostream>
#include <fstream>
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
  Vertex* inputVert;
  if(argc == 2){
    filename = argv[1];
    inputStr = "";
  }
  if(argc == 3){
    filename = argv[1];
    inputStr = argv[2];
  }
  






  ClassGraph g(filename);
  //g.makeAcyclic();
  std::cout << g.toMathematicaForm() << std::endl;
  std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
  Vertex* start = g.getStart();
  Vertex* end = g.getEnd();



  //BFS USER CODE//////////////////////////////////////////////////////////////////////////////////////////
  BFS traversal(&g, start);                    //create traversal, start at vert 0
  
  ofstream BFSFile;
  BFSFile.open ("./Outputs/BFS_Full_File.txt");
  BFSFile << "BFS Iterator on all courses within file\n\n";
  
  for (auto it = traversal.begin(); it != traversal.end(); ++it)
  {
    Vertex v = **it;
    BFSFile << v;
    BFSFile << "\n";
  }
  BFSFile.close();

  if(inputStr != "")
  {
    inputVert = g.getVertexByName(inputStr);

    BFS traversal2(&g, inputVert);

    ofstream BFSFile2;
    BFSFile2.open ("./Outputs/BFS_From_Course.txt");
    BFSFile2 << "BFS Iterator on all courses starting at user ARG2\n\n";

    for (auto it = traversal2.begin(); it != traversal2.end(); ++it)
    {
      Vertex v = **it;
      BFSFile2 << v;
      BFSFile2 << "\n";
    }
  BFSFile2.close();
  }
  
  //BETWEENESS CENTRALITY TEST CODE////////////////////////////////////////////////////////////////////////
  ofstream BCFile;
  BCFile.open ("./Outputs/Betweeness_Full_File.txt");
  BCFile << "Betweeness Centrality on all courses within file\n\n";
  




  g.initLayers();
  g.generateBetweennessCentrality(true, false);
  Vertex mostImportantVertex;
  double maxScore = std::numeric_limits<double>::min();
  for(std::pair<Vertex, double> betwCent : *g.getBetweennessCentrality()){
    Vertex v = betwCent.first;
    double score = betwCent.second;
    BCFile << "The betweenness centrality of " << v << " is " << score << "\n";

    if(score > maxScore){
      maxScore = score;
      mostImportantVertex = v;
    }
  }

  BCFile << "\nThe most central vertex in the graph is " << mostImportantVertex << " with a centrality of " << maxScore << std::endl;

  BCFile.close();

  //LAYERED GRAPH DRAWING CODE/////////////////////////////////////////////////////////////////////////

  
  LGD gLGD(&g,start);
  if(inputStr != ""){
    inputVert = g.getVertexByName(inputStr);
  } else{
    inputVert = g.getStart();
  }
  Image output;

  if (inputStr != "")
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