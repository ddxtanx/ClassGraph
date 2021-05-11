#pragma once

#include "../Graph/Graph.h"
//#include "../cs225/PNG.h"
#include "../Stickers/StickerSheet.h"
#include <vector>

class LGD
{
    public:
    LGD();                          //constructors
    LGD(Graph & g, Vertex & v);     //create by reference for easy 
    ~LGD();                         //destructor
    LGD(Graph * g, Vertex * v);     //create by pointer for flexibility

    LGD(const LGD &other);          //copy constructor
    const LGD & operator= (const LGD & other);     //copy constructor overload

    void makeDummyVerts();

    /**  /////////////////////////////////////////////////////////////////////////////////////////////////////
     * Uses a layered graph drawing algorithm to organize and render a PNG that shows the start
     * course's prerequisit graph
     *
     * @param start     - optional argument to change the start vertex before building and rendering
     */  /////////////////////////////////////////////////////////////////////////////////////////////////////
    Image drawGraph();                    //creates PNG of a layered style of all courses that are prerequisit to the start course
    Image drawGraph(Vertex * start);      //same as drawGraph() but modifies start point before running
    Image drawGraph(Vertex & start);


    /**  /////////////////////////////////////////////////////////////////////////////////////////////////////
     * takes in coordinates of 2 Image objs and draws a line between them
     * Note: Image 1 is physically above Image 2 in desired output PNG
     *
     * @param pic1  - Image or vertex coordinates that are physically above pic2 in output PNG
     * @param pic2  - Image or vertex coordinates that are physically below pic1 in output PNG
     * @param v1     - Vertex ptr/ref thats above
     * @param v2     - Vertex ptr/ref below
     * @param x     - coordinate of left most edge of vertex drawing
     * @param y     - coordinate of upper most edge of vertex drawing
     * @param color - optional HSLAPixel argument to change color of line, defaults to black
     */  /////////////////////////////////////////////////////////////////////////////////////////////////////
    void drawEdge(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
    void drawEdge(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel color);
    void drawEdge(Image * pic1, Image * pic2);
    void drawEdge(Image & pic1, Image & pic2);
    void drawEdge(Vertex * v1, Vertex * v2);
    void drawEdge(Vertex & v1, Vertex & v2);


    /**  /////////////////////////////////////////////////////////////////////////////////////////////////////
     * takes in Vertex info and a position to put it in the stickerSheet (stickers_)
     * 
     * @param name  - input custom name to put in vertex. Must be either all letters,
     *                  letters, then a space, then numbers, or
     *                  just numbers, and is limited to 8 Total characters
     * @param v     - Vertex obj or ptr to draw (only uses getName() )
     * @param x     - coordinate of left most edge of vertex drawing
     * @param y     - coordinate of upper most edge of vertex drawing
     * 
     * @return      - Index of Image that was added to sticker sheet
     */  /////////////////////////////////////////////////////////////////////////////////////////////////////
    int drawVertex(std::string  name, unsigned int x1, unsigned int y1, cs225::HSLAPixel color);
    int drawVertex(std::string  name, unsigned int x1, unsigned int y1);
    int drawVertex(Vertex * v, unsigned int x1, unsigned int y1);
    int drawVertex(Vertex & v, unsigned int x1, unsigned int y1);


    private:
    Image pic_;             //sticker output Image, used for edge drawing and final picture
    Image text_;            //character storage png
    Image background_;      //background, typically plain white
    Image oval_;            //holds vertex drawing border
    Image skip_;            //holds dummy vertex line pass thru

    StickerSheet* stickers_; //Sticker sheet for vertex rendering

    Vertex * start_;        //Node to show prereq tree for
    Graph * graph_;         //graph structure for data
};
