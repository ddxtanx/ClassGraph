#include "ClassGraph.h"
#include "dataConvert.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include "utils.h"
Vertex* ClassGraph::getOrCreateVertex(std::string courseName){
    std::string modifiedName = courseName;
    for(char& c: modifiedName){
        c = toupper(c);
    }
    Utils::trim(modifiedName);
    int index = Utils::hashCourseName(modifiedName);
    if(index == -1){
        std::cout << "Bad course name: " << modifiedName << std::endl;
        return nullptr;
    }
    if(vertexMap_[index] == nullptr){
        Vertex* currVertex = new Vertex(modifiedName);
        vertexMap_[index] = currVertex;
        addVertex(currVertex);
        return currVertex;
    } else{
        return vertexMap_[index];
    }
}
ClassGraph::ClassGraph(const std::string fileName){
    //std::vector<std::vector<std::string>> CS_data=DataConvert::getData("Courses-and-prereqs/CS_courses.dat");
    //std::vector<std::vector<std::string>> ECE_data=DataConvert::getData("Courses-and-prereqs/ECE_courses.dat");
    std::vector<std::vector<std::string>> ALL_COURSE_data=DataConvert::getData("Courses-and-prereqs/ECE_courses.dat");
    //std::vector<std::vector<std::string>> MATH_data=DataConvert::getData("Courses-and-prereqs/MATH_courses.dat");
    //std::vector<std::vector<std::string>> PHYS_data=DataConvert::getData("Courses-and-prereqs/PHYS_courses.dat");
    //std::vector<std::vector<std::string>> ALL_COURSE_data = DataConvert::getData("Courses-and-prereqs/AllPrereqs.dat");
    std::vector<std::vector<std::string>> ALL_COURSE_data = DataConvert::getData(fileName);

    int numEntries = ALL_COURSE_data.size() + 1;
    int numClassIDs = 800*Utils::numDepts;
    vertexMap_.resize(numClassIDs);
    resizeAdjMatrix(numEntries);
    Vertex* startVertex = new Vertex("START");
    startVertex -> setId(numEntries - 1); 
    addVertex(startVertex);
    start_ = startVertex;
    for(unsigned i=0;i<ALL_COURSE_data.size();i++)
    {
        std::vector<std::string> firstTok=ALL_COURSE_data[i];
        std::string baseCourseName = firstTok[0];
        Vertex* currVertex = getOrCreateVertex(baseCourseName);
        bool hasNoPrereq = true;
        for(unsigned i=1;i<firstTok.size();i++)
        {
            std::string prereqCourseName = firstTok[i];
            Utils::trim(prereqCourseName);
            if(!prereqCourseName.empty()){  
                Vertex* toVer = getOrCreateVertex(prereqCourseName);
                addEdge(toVer, currVertex, 1);
                hasNoPrereq = false;
            }
        }
        if(hasNoPrereq){
            addEdge(startVertex, currVertex, 1);
        }
    }
}

Vertex*& ClassGraph::getStart(){
    return start_;
}
ClassGraph::~ClassGraph(){
    for(Vertex* vert: vertexMap_){
        if(vert != nullptr){
            delete vert;
        }
    }
}