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
    //std::vector<std::vector<std::string>> MATH_data=DataConvert::getData("Courses-and-prereqs/MATH_courses.dat");
    //std::vector<std::vector<std::string>> PHYS_data=DataConvert::getData("Courses-and-prereqs/PHYS_courses.dat");
    Utils::initializeDepts(fileName);
    Vertex::setCountNum(0);
    std::vector<std::vector<std::string>> ALL_COURSE_data = DataConvert::getData(fileName);

    int numEntries = ALL_COURSE_data.size() + 1;
    int numClassIDs = 1000*Utils::numDepts;
    vertexMap_.resize(numClassIDs);
    resizeAdjMatrix(numEntries);
    Vertex* startVertex = new Vertex("START");
    addVertex(startVertex);
    start_ = startVertex;
    for(unsigned i=0;i<ALL_COURSE_data.size();i++)
    {
        std::vector<std::string> firstTok=ALL_COURSE_data[i];
        if(firstTok.empty()){
            std::cout << "Empty tok at line " << i << std::endl;
            continue;
        }
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

ClassGraph& ClassGraph::operator=(const ClassGraph& ot){
    std::cout << "assigning a class graph" << std::endl;
    if(&ot != this){
        this -> ~ClassGraph();
    }
    Graph::operator=(ot);
    start_ = new Vertex(*ot.start_);
    return *this;
}

ClassGraph::ClassGraph(const ClassGraph& ot) : Graph(ot){
    std::cout << "Copy constructing a class graph" << std::endl;
    start_ = new Vertex(*ot.start_);
}

void ClassGraph::makeAcyclic(){
    Graph::makeAcyclic(start_);
}