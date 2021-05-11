#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <vector>
class Vertex{
    public:
        Vertex();
        Vertex(std::string name);    //constructor
        
        void connectTo(Vertex* to);  //place vertex in group of edges (courses that have OR implementation)
        void disconnectTo(Vertex* to); 

        void connectFrom(Vertex* from);
        void disconnectFrom(Vertex* from);

        //Edge edgePointingToVertex(Vertex* to);            //returns edge that goes from *this to target vertex
        bool pointsTo(Vertex* to);                               //does this vertex point to an other (directional edge checking)



        std::vector<Vertex*> getVerticesPointedTo();             //returns all vertecies that *this points to
        std::vector<Vertex*> getVerticesPointedFrom();

        size_t getNumPointedTo();
        size_t getNumPointedFrom();
        
        std::string getName() const;
        size_t getId() const;

        void setId(size_t id);

        unsigned getLayer() const;
        void setLayer(unsigned layer);

        bool operator==(const Vertex v) const;

        friend std::ostream& operator<<(std::ostream& os, const Vertex& v){
            os << v.getName();
            return os;
        }

        static void setCountNum(size_t c);


        unsigned int xPos = 0;  //used in drawGraph
        unsigned int yPos = 0;
    private:
        static size_t count;
        std::vector<Vertex*> pointsTo_;  //Collection of vertices v such that there is an edge e where e.getFrom == this and e.getTo == v
        std::vector<Vertex*> pointsFrom_;  //Collection of vertices v such that there is an edge e where e.getFrom == v and e.getTo == this

        unsigned layer_; //Layer
        size_t numPointsTo;
        size_t numPointsFrom;
        std::string name_;                                  //course data
        size_t id_;                                 //id used for the adjacency graph
        
        

};

namespace std{
    template<>
    struct hash<Vertex>{
        size_t operator()(const Vertex& v) const{
            return v.getId();
        }
    };
};