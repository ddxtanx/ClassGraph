#pragma once
#include "ColoredEdgeSet.h"
#include "ColoredEdge.h"
#include <string>
#include <vector>
class ColoredVertex{
    public:
        ColoredVertex(std::string name);    //constructor
        
        void connectInEdgeSet(ColoredVertex* to, size_t edgeSetColor);  //place vertex in group of edges (courses that have OR implementation)
        std::vector<ColoredEdgeSet> getEdgeSets();                      //get vector of sets of edges (each set of edges has AND logic applied between)

        int edgeSetContainingVertex(ColoredVertex* to);                 //returns edgeSet number that contains edge that points from *this to target
        ColoredEdge edgeContainingVertex(ColoredVertex* to);            //returns edge that goes from *this to target vertex
        bool pointsTo(ColoredVertex* to);                               //does this vertex point to an other (directional edge checking)

        std::vector<ColoredVertex*> getVerticesPointedTo();             //returns all vertecies that *this points to


        
    private:
        size_t numEdgeSets;                                 //self explanatory
        std::vector<ColoredEdgeSet> edgeSets_;              //contains all edgeSets from *this
        std::vector<ColoredVertex*> adjacentVertices_;      //contains all verticies *this points to

        std::string name_;                                  //course data
        size_t id_;
};