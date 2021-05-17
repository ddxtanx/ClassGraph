#include "ClassGraph.h"
#include "dataConvert.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <queue>
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
    Utils::initializeDepts(fileName);
    Vertex::setCountNum(0);
    std::vector<std::vector<std::string>> ALL_COURSE_data = DataConvert::getData(fileName);

    int numEntries = ALL_COURSE_data.size() + 2;
    int numClassIDs = 1000*Utils::numDepts;
    vertexMap_.resize(numClassIDs);
    resizeAdjMatrix(numEntries);
    Vertex* startVertex = new Vertex("START");
    Vertex* endVertex = new Vertex("END");
    addVertex(startVertex);
    addVertex(endVertex);
    start_ = startVertex;
    end_ = endVertex;
    for(unsigned i=0;i<ALL_COURSE_data.size();i++)
    {
        std::vector<std::string> firstTok=ALL_COURSE_data[i];
        if(firstTok.empty()){
            std::cout << "Empty tok at line " << i << std::endl;
            continue;
        }
        std::string baseCourseName = firstTok[0]; //Course name
        Vertex* currVertex = getOrCreateVertex(baseCourseName);
        bool hasPrereqs = false;
        for(unsigned i=1;i<firstTok.size();i++)
        {
            std::string prereqCourseName = firstTok[i];  //Prerequisite of baseCourseName
            Utils::trim(prereqCourseName);
            if(!prereqCourseName.empty()){  
                hasPrereqs = true;
                Vertex* toVer = getOrCreateVertex(prereqCourseName);
                addEdge(currVertex, toVer);  //Class points to its prerequisite
            }
        }
        if(!hasPrereqs){
            addEdge(currVertex, end_);
        }
    }
    for(Vertex* v: vertices_){
        if(v->getNumPointedFrom() == 0 && v != startVertex && v != endVertex){
            addEdge(startVertex, v); //Start points to ultimate classes (classes that are not prereqs for other classes)
        }
    }
}

Vertex*& ClassGraph::getStart(){
    return start_;
}

Vertex*& ClassGraph::getEnd(){
    return end_;
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

Vertex*& ClassGraph::getVertexByName(std::string name){
    if(name == "START"){
        return start_;
    }
    if(name == "END"){
        return end_;
    }
    size_t hash = Utils::hashCourseName(name);
    return vertexMap_[hash];
}

void ClassGraph::makeAcyclic(){
    std::unordered_map<Vertex*, std::unordered_map<Vertex*, bool>> histories;
    std::unordered_map<Vertex*, unsigned int> heights;
    std::queue<Vertex*> callStack;
    Matrix<bool> connectedTo(getVerticesSize(), getVerticesSize(), false);
    callStack.push(end_);
    heights[end_] = 0;
    std::vector<Edge> newEdges;
    while(!callStack.empty()){
        Vertex* head = callStack.front();
        callStack.pop();

        auto neighs = head -> getVerticesPointedFrom();
        for(auto pair : histories[head]){
            for(Vertex* neigh : neighs){
                if(pair.second){
                    histories[neigh][pair.first] = true;
                }
            }
        }
        for(Vertex* neigh : neighs){
            if(heights[neigh] < heights[head] + 1){
                heights[neigh] = heights[head] + 1;
            }
            histories[neigh][head] = true;
            if(histories[head][neigh] && heights[neigh] > heights[head]){
                std::cout << "Removing edge between " << *neigh << " and " << *head << std::endl;
                removeEdge(neigh, head);
                makeAcyclic();
                return;
            } else{
                size_t nId = neigh -> getId();
                size_t hId = head -> getId();
                if(!connectedTo.getVal(nId, hId)){
                    Edge e(neigh, head);
                    newEdges.push_back(e);
                    connectedTo.setVal(nId, hId, true);
                }
                callStack.push(neigh);
            }
        }
    }
    for(Vertex* v : vertices_){
        if(v != start_ && v != end_ && v -> getNumPointedFrom() == 0){
            addEdge(start_, v);
        }
    }
    edges_ = newEdges;
}