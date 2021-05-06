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


//test1
TEST_CASE("BFS iterator starts at the start point", "[weight=2][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[4];                        //pick out 4th vertice

    BFS traversal(&g, start); 
    REQUIRE( *(traversal.begin()) == start );
}
//test2
TEST_CASE("BFS visits the correct vertex first", "[weight=2][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[3];                        //pick out 4th vertice   (CSE 300)
    
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();
    ++it;
    std::vector<Vertex*> vert2 = start->getVerticesPointedTo();
    REQUIRE( *(it) == vert2[0]);
}


//test3
TEST_CASE("BFS visits all courses with start as a prereq", "[weight=1][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[1];                        //pick out 2nd vertice   (CSE 100)
  
    BFS traversal(&g, start); 
    unsigned count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {           
        count++;
    }
    //should traverse cse100->cse200->cse300->adv101
        //i.e. 4 cycles
    REQUIRE( count == 4 );

    std::cout << std::endl;


    
    start = verts[5];                        //pick out 6th vertice   (ANTH 101)
    BFS traversal2(&g, start); 
    count = 0;
    for (BFS::Iterator it = traversal2.begin(); it != traversal2.end(); ++it)
    {
        count++;
    }
    //should go ANTH101->STE115->ANTH201->STE215(skip ste215 repeat edge)->ANTH301->STE315
    //ie 6 cycles
    REQUIRE( count == 6 );
}

//test4
TEST_CASE("BFS visits only single vertex in disconnected vertex", "[weight=1][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[9];                        //pick out 9th vertice   (ANTH 107)
  
    BFS traversal(&g, start); 
    unsigned count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
        count++;
    }
    REQUIRE( count == 1 );
}

//test 5
TEST_CASE("BFS iterator visits anth101 points in the correct order", "[weight=1][part=1]") {
    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[5];                        //pick out 14th vertice   (math213)
  
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();

  REQUIRE( *it == verts[5] ); ++it;

  REQUIRE( *it == verts[7] ); ++it;  
  REQUIRE( *it == verts[8] ); ++it;

  REQUIRE( *it == verts[11] ); ++it;  
  REQUIRE( *it == verts[10] ); ++it;

  REQUIRE( *it == verts[12] );
  
}

//test6
TEST_CASE("BFS iterator visits all (start) points in the correct order", "[weight=1][part=1]") {
    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[0];                        //pick out 14th vertice   (math213)
  
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();
    /*
    std::cout << "Printing vertexes in graph obj: " << std::endl;
    int count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
      std::cout << count << " " << **it << std::endl;
      ++count;

    }
    */


   //should visit all vertecies with NO prereqs first
  REQUIRE( *it == verts[0] ); ++it;
  REQUIRE( *it == verts[1] ); ++it;  //cse100
  REQUIRE( *it == verts[5] ); ++it; //anth101
  REQUIRE( *it == verts[6] ); ++it;  //ste100
  REQUIRE( *it == verts[9] ); ++it;     //anth107
  REQUIRE( *it == verts[13] ); ++it;    //math231
  REQUIRE( *it == verts[14] ); ++it;    //math213
  //then visit next level in each individual prereq chain
  REQUIRE( *it == verts[2] ); ++it;  //cse200
  REQUIRE( *it == verts[7] ); ++it;  //etc
  REQUIRE( *it == verts[8] ); ++it; 
  REQUIRE( *it == verts[10] ); ++it;
  REQUIRE( *it == verts[15] ); ++it;
  REQUIRE( *it == verts[16] ); ++it;
  //3rd level
  REQUIRE( *it == verts[3] ); ++it; 
  REQUIRE( *it == verts[11] ); ++it;
  REQUIRE( *it == verts[17] ); ++it; 
  REQUIRE( *it == verts[18] ); ++it;
  //4th level
  REQUIRE( *it == verts[4] ); ++it;
  REQUIRE( *it == verts[12] ); ++it;
}

TEST_CASE("test")
{
    int i=5;
    i++;
    REQUIRE(i==6);
}