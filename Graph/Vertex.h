#pragma once
#include <string>
#include <vector>
#include <iostream>
class Vertex{
    public:
        static int count;
        Vertex();
        Vertex(std::string name);    //constructor
        
        void connectTo(Vertex* to);  //place vertex in group of edges (courses that have OR implementation)

        //Edge edgePointingToVertex(Vertex* to);            //returns edge that goes from *this to target vertex
        bool pointsTo(Vertex* to);                               //does this vertex point to an other (directional edge checking)


        std::vector<Vertex*> getVerticesPointedTo();             //returns all vertecies that *this points to
        std::string getName() const;
        size_t getId() const;

        void setId(int id);


        bool operator==(const Vertex v) const;

        friend std::ostream& operator<<(std::ostream& os, const Vertex& v){
            os << "Vertex: "<< v.getName();
            return os;
        }
    private:
        std::vector<Vertex*> adjacentVertices_;      //contains all verticies *this points to
        std::string name_;                                  //course data
        size_t id_;                                 //id used for the adjacency graph
};