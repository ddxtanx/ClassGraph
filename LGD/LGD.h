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

    LGD(const LGD &other);          //copy constructor
    ~LGD();                         //destructor
    const LGD & operator= (const LGD & other); 	//copy constructor overload

    Image drawGraph();                    //creates PNG of a layered style of all courses that are prerequisit to the start course
    Image drawGraph(Vertex * start);      //same as drawGraph() but modifies start point before running
    Image drawGraph(Vertex & start);

    void setStart(Vertex * s);         //changes start value
    void setStart(Vertex & s);

    
    void drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2);
    void drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel color);
    void drawVertex(std::string  name, unsigned int & x1, unsigned int & y1);
    void drawVertex(std::string  name, unsigned int & x1, unsigned int & y1, cs225::HSLAPixel color);

    private:


    Image pic_;             //sticker output Image, used for edge drawing and final picture
    Image text_;            //character storage png
    Image background_;
    Image oval_;

    StickerSheet * stickers_; //Sticker sheet for vertex rendering

    Vertex * start_;        //Node to show prereq tree for
    Graph * graph_;         //graph structure for data
};
