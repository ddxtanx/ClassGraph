#pragma once

#include "../Graph/Graph.h"
//#include "../cs225/PNG.h"
#include "../Stickers/StickerSheet.h"
#include <vector>

class LGD
{
    public:
    LGD();                          //constructors
    LGD(Graph & g, Vertex & v);     //create by reference for easy use
    LGD(Graph * g, Vertex * v);     //create by pointer for flexibility
    ~LGD();                         //destructor
    const LGD & operator= (const LGD & other); 	//copy constructor

    PNG * drawGraph();                    //creates PNG of a layered style of all courses that are prerequisit to the start course
    PNG * drawGraph(Vertex * start);      //same as drawGraph() but modifies start point before running
    PNG * drawGraph(Vertex & start);

    void setStart(Vertex * start);         //changes start value
    void setStart(Vertex & start);

    private:
    void drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2);
    void drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel & color);
    void drawVertex(std::string, unsigned int & x, unsigned int & y);
    void drawVertex(std::string, unsigned int & x, unsigned int & y, cs225::HSLAPixel & color);

    Image pic_;             //sticker output Image, used for edge drawing and final picture
    Image text_;            //character storage png
    Image background_;
    Image oval_;

    StickerSheet stickers_; //Sticker sheet for vertex rendering

    Vertex * start_;        //Node to show prereq tree for
    Graph * graph_;         //graph structure for data
};
