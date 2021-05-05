#include "../cs225/catch/catch.hpp"
#include <iostream>
#include "../dataConvert.h"
#include "../Davids_Work/BFS.h"
#include "../Graph/Graph.h"
#include "../ClassGraph.h"
#include "../utils.h"
/*
TEST_CASE("BFS iterator small test")
{
    std::string filename = "../Courses-and-prereqs/TestData.dat";    //load data into graph
    Utils::initializeDepts(filename);
    ClassGraph g(filename);
  
    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = g.getStart();

    BFS traversal(&g, start);                    //create traversal, start at vert 0
    BFS::Iterator it = traversal.begin();
    for (; it != traversal.end(); ++it)
    {
        if(*it == nullptr)
        {
            continue;
        }
        Vertex v = **it;
        std::cout << "Classes that require " << v << ": ";
        for(Vertex* vp : v.getVerticesPointedTo())
        {
            std::cout << *vp << ", ";
        } 
    std::cout << std::endl;
    }



}
*/
std::string filename = "./Courses-and-prereqs/TestData.dat";
ClassGraph g(filename);

TEST_CASE("BFS iterator starts at the start point", "[weight=2][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[4];                        //pick out 4th vertice
  
    BFS traversal(&g, start); 
    REQUIRE( *(traversal.begin()) == start );
}

TEST_CASE("BFS visits the correct vertex first", "[weight=2][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices



    std::cout << "Printing First 15 vertexes in graph obj: " << std::endl;
    int count = 0;
    for (std::vector<Vertex*>::iterator it = verts.begin(); it != verts.end(); ++it)
    {
      std::cout << count << " " << **it << std::endl;
      ++count;
      if (count == 15)
        break;

    }




    Vertex* start = verts[4];                        //pick out 4th vertice   (CSE 300)
    
    std::cout << *start << std::endl;
  
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();
    ++it;
    //std::vector<Vertex*> temp = start->getVerticesPointedTo();
    REQUIRE( *(it) == (start->getVerticesPointedTo())[0]);
}

TEST_CASE("BFS visits all courses with start as a prereq", "[weight=1][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[4];                        //pick out 4th vertice   (CSE 300)
  
    BFS traversal(&g, start); 
    unsigned count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
        count++;
    }
    REQUIRE( count == 3 );

    start = verts[5];                        //pick out 4th vertice   (CSE 300)
    count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
        count++;
    }
    REQUIRE( count == 5 );
}

TEST_CASE("BFS visits only single vertex in disconnected vertex", "[weight=1][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[9];                        //pick out 4th vertice   (CSE 300)
  
    BFS traversal(&g, start); 
    unsigned count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
        count++;
    }
    REQUIRE( count == 1 );
}

/*
TEST_CASE("BFS iterator visits all points in the correct order", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  BFS t(png, startPoint, 0.2);
  ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(0, 0) ); ++it;

  REQUIRE( *it == Point(1, 0) ); ++it;  
  REQUIRE( *it == Point(0, 1) ); ++it;

  REQUIRE( *it == Point(2, 0) ); ++it;  
  REQUIRE( *it == Point(0, 2) ); ++it;

  REQUIRE( *it == Point(3, 0) ); ++it;
  REQUIRE( *it == Point(0, 3) ); ++it;

  REQUIRE( *it == Point(3, 1) ); ++it;
  REQUIRE( *it == Point(1, 3) ); ++it;
  
  REQUIRE( *it == Point(3, 2) ); ++it;
  REQUIRE( *it == Point(2, 3) ); ++it;

  REQUIRE( *it == Point(3, 3) ); ++it;
}

*/


TEST_CASE("test")
{
    int i=5;
    i++;
    REQUIRE(i==6);
}