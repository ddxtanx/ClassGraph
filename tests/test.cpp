#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <sstream>
#include "../dataConvert.h"
#include "../Davids_Work/BFS.h"
#include "../Graph/Graph.h"
#include "../ClassGraph.h"
#include "../utils.h"
#include <unordered_map>


std::string filename = "./Courses-and-prereqs/TestData.dat";
ClassGraph g(filename);



TEST_CASE("BFS setup")
{
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
        //std::cout << "Classes that require " << v << ": ";
        for(Vertex* vp : v.getVerticesPointedTo())
        {
        //    std::cout << *vp << ", ";
        } 
    //std::cout << std::endl;
    }
}


//test1
TEST_CASE("BFS iterator starts at the start point", "[weight=2][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[4];                        

    BFS traversal(&g, start); 
    REQUIRE( *(traversal.begin()) == start );
}
//test2
TEST_CASE("BFS visits the correct vertex first", "[weight=2][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[3];                       
    
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();
    ++it;
    std::vector<Vertex*> vert2 = start->getVerticesPointedTo();
    REQUIRE( *(it) == vert2[0]);
}


//test3
TEST_CASE("BFS visits all courses with start as a prereq", "[weight=1][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[4];                        
  
    BFS traversal(&g, start); 
    unsigned count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {           
        count++;
    }
    REQUIRE( count == 4 );

    std::cout << std::endl;


    
    start = verts[5];                        //pick out 6th vertice   (ANTH 101)
    BFS traversal2(&g, start); 
    count = 0;
    for (BFS::Iterator it = traversal2.begin(); it != traversal2.end(); ++it)
    {
        count++;
    }
    REQUIRE( count == 5 );
}

//test4
TEST_CASE("BFS visits only single vertex in disconnected vertex", "[weight=1][part=1]") {

    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[10];                          //ANTH 107                
  
    BFS traversal(&g, start); 
    unsigned count = 0;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
        count++;
        
    }
    REQUIRE( count == 2 );      //ANTH->END     ie 2 cycles
}

//test 5
TEST_CASE("BFS iterator visits STE 315 points in the correct order", "[weight=1][part=1]") {
    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[13];                   
  
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();

  REQUIRE( *it == verts[13] ); ++it;

  REQUIRE( *it == verts[12] ); ++it;  
  REQUIRE( *it == verts[9] ); ++it;

  REQUIRE( *it == verts[8] ); ++it;  
  REQUIRE( *it == verts[6] ); ++it;

  REQUIRE( *it == verts[7] );
  
}

//test6
TEST_CASE("BFS iterator visits all (start) points in the correct order", "[weight=1][part=1]") {
    std::vector<Vertex*> & verts = g.getVertices();  //get reference to vertices
    Vertex* start = verts[0];                        //pick out 0th vertice   (start)
  
    BFS traversal(&g, start); 
    BFS::Iterator it = traversal.begin();
   
   //should visit all vertecies with NO prereqs first
  REQUIRE( *it == verts[0] ); ++it; //start
  REQUIRE( *it == verts[13] ); ++it;    //STE 315
  REQUIRE( *it == verts[11] ); ++it;    //ANTH 301
  REQUIRE( *it == verts[10] ); ++it;    //ANTH107
  REQUIRE( *it == verts[5] ); ++it;     //ADV 101
  REQUIRE( *it == verts[12] ); ++it;   
  REQUIRE( *it == verts[7] ); ++it;    
  REQUIRE( *it == verts[9] ); ++it;
   ++it;  //END, special vertex no pointer available
  REQUIRE( *it == verts[4] ); ++it;     
  REQUIRE( *it == verts[8] ); ++it;
  REQUIRE( *it == verts[6] ); ++it;
  REQUIRE( *it == verts[3] ); ++it;
  REQUIRE( *it == verts[2] ); ++it; 
  
}

//test7
TEST_CASE("BFS iterator visits all points in large data set", "[weight=5][part=1]") {

    std::string filename2 = "./Courses-and-prereqs/AllPrereqs.dat";
    ClassGraph h(filename2);
    std::vector<Vertex*> & verts = h.getVertices();  //get reference to vertices
    Vertex* start = h.getStart();                        //pick out 0th vertice   (start)
  
    BFS traversal(&h, start); 
    BFS::Iterator it = traversal.begin();
    unsigned count = 0;
    std::cout << "# of verts in graph: " << verts.size()  << std::endl;
    std::cout << "# of verts pointed to by start (how many disjoint sets): " << start->getVerticesPointedTo().size()  << std::endl;
    for (BFS::Iterator it = traversal.begin(); it != traversal.end(); ++it)
    {
        count++;
    }
    //Some classes have prerequisites that have not been offered since spring 2020, but they are still nonetheless prerequisites.
    REQUIRE( count >= 7244 );

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//I calculated all of the true betweenness centralities with mathematica. To verify that I didn't just copy-pasta 
//What the results of my version of the betweenness were, you can run [GRAPH].getMathematicaForm(); and use it
//To calculate the true betweenness centrality. A point to note is that if you generate betweenness centrality 
//Backwards then you should generate the mathematica graph backwards.
TEST_CASE("Betweenness centrality works on line graph", "[weight=5][part=2]"){
    ClassGraph lineTest("./Courses-and-prereqs/LongPrereqs.dat");
    lineTest.generateBetweennessCentrality(true, false);
    Vertex* start = lineTest.getStart();
    Vertex* end = lineTest.getEnd();
    auto vertices = lineTest.getVertices(); //{start, end, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    auto betwCent = lineTest.getBetweennessCentrality();
    for(std::pair<Vertex, double> pair : *betwCent){
        Vertex v = pair.first;
        double d = pair.second;
        if(v == *start){
            REQUIRE(d == 0);
        }
        else if(v == *end){
            REQUIRE(d == 0);
        }
        else{
            size_t id = v.getId();
            double factor1 = (double)id - 1;
            double factor2 = 12 - (double)id;
            REQUIRE(d == factor1*factor2);
        }
    }
}

TEST_CASE("Betweenness centrality works on more complicated graph", "[part=2]"){
    ClassGraph centralityComplicated("./Courses-and-prereqs/CentralityTestComplicated.dat");
    centralityComplicated.generateBetweennessCentrality(false, false);
    auto verts = centralityComplicated.getVertices(); // {s,e,8,9,10,6,5,7,4,3,1,2}
    std::vector<double> expected_centralities = {0,0,73.0/30,10.0/3,67.0/30,4.2,13,2.8,13,6,1,1};  //Calculated via mathematica
    int index = 0;
    for(auto pair : *centralityComplicated.getBetweennessCentrality()){
        double v = pair.second;
        REQUIRE(abs(v - expected_centralities[index]) <= .00001);
        index++;
    }
}

TEST_CASE("Betweenness centrality works on test graph", "[part=2]"){
    std::map<std::string, double> expectedCentrality = {
        {"START", 0},
        {"END", 0},
        {"CSE 100", 3},
        {"CSE 200", 5},
        {"CSE 300", 5},
        {"ADV 101", 3},
        {"ANTH 101", 17.0/6},
        {"STE 100", 13.0/6},
        {"STE 115", 13.0/3},
        {"ANTH 201", 11.0/3},
        {"ANTH 107", 1},
        {"ANTH 301", 3},
        {"STE 215", 6},
        {"STE 315", 2},
        {"MATH 231", 2},
        {"MATH 213", 2},
        {"MATH 347", 4},
        {"CS 225", 6},
        {"MATH 412", 1},
        {"CS 374", 2}
    }; 
    ClassGraph testDataGraph("./Courses-and-prereqs/TestData.dat");
    testDataGraph.generateBetweennessCentrality(true, false);
    auto centrality = *testDataGraph.getBetweennessCentrality();
    for(auto pair : expectedCentrality){
        Vertex* v = testDataGraph.getVertexByName(pair.first);
        std::stringstream ss;
        ss << "Vertex " << *v << " has centrality of " << centrality[*v] << " but it should be " << pair.second;
        INFO(ss.str())
        INFO(testDataGraph.toMathematicaForm(true));
        REQUIRE(abs(centrality[*v] - pair.second) <= .0001);
        
    }
}
TEST_CASE("example test", "[weight=5][part=1]") {

    int i = 5;
    ++i;
    REQUIRE( i == 6);
}