#pragma once
#include "ColoredEdgeSet.h"
#include "ColoredEdge.h"
#include <string>
#include <vector>
class ColoredVertex{
    public:
        ColoredVertex(std::string name);
        
        void connectInEdgeSet(ColoredVertex* to, size_t edgeSetColor);

        std::vector<ColoredEdgeSet> getEdgeSets();

        int edgeSetContainingVertex(ColoredVertex* to);
        ColoredEdge edgeContainingVertex(ColoredVertex* to);
        bool pointsTo(ColoredVertex* to);

        std::vector<ColoredVertex*> getVerticesPointedTo();
    private:
        size_t numEdgeSets;
        std::vector<ColoredEdgeSet> edgeSets_;
        std::vector<ColoredVertex*> adjacentVertices_;
        std::string name_;
        size_t id_;
};