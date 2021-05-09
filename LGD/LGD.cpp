#include "LGD.h"
#include "../cs225/PNG.h"
#include "../Stickers/Image.h"
#include <cmath>

using namespace cs225;
// constructors
LGD::LGD() 
: pic_(Image()), stickers_(StickerSheet(pic_, 10u)), start_(NULL),  graph_(NULL)
{ 
    text_.readFromFile("./LGD/text.png");
    oval_.readFromFile("./LGD/oval.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
}                      
LGD::LGD(Graph & g, Vertex & v)  
: pic_(Image()), stickers_(StickerSheet(pic_, 10u)), start_(&v), graph_(&g)
{
    text_.readFromFile("./LGD/text.png");
    oval_.readFromFile("./LGD/oval.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
    //stickers_(const Image &picture, unsigned max);
}   
LGD::LGD(Graph * g, Vertex * v)    
: pic_(Image()), stickers_(StickerSheet(pic_, 10u)), start_(v), graph_(g)
{
    text_.readFromFile("./LGD/text.png");
    oval_.readFromFile("./LGD/oval.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
    //stickers_(const Image &picture, unsigned max);
} 

const LGD & LGD::operator= (const LGD & other)
{
    stickers_ = other.stickers_;
    pic_ = other.pic_;
    start_ = other.start_;
    graph_ = other.graph_;
    return *this;
}


void LGD::setStart(Vertex * start)
{   start_ = start;     }
void LGD::setStart(Vertex & start)
{   start_ = &start;    }

//needs testing
void LGD::drawVertex(std::string name, unsigned int x1, unsigned int y1, cs225::HSLAPixel color)
{
    //check dict if dept name has already been made
    //Create a department name PNG from cutting and pasting text.png if not made already
    //place png in dictionary

  unsigned int xOffset = 7;
  unsigned int yOffset = 10;
  unsigned int currPos = 0;
  for (char& c : name)
  {
    unsigned int position;
    if (c - ' ' == 0)
    {
      currPos = 70; //if space is encountered, set the spacing to be consistant
      continue;     
    }
    else if (c - '0' < 10)                        //if number is encountered
    {
      position = 14*(26 + (c-'0')); //gets position of character in text.png
    }
    else if (c - 'A' > 0)                         //if letter is encountered
    {
      position = 14*(c-'A');        //gets position of character in text.png
    }

    //copies letter from text.png to oval.png, overwriting any past vertex
    for (unsigned int x = 0; x < 14; ++x)
    {
      for (unsigned int y = 0; y < 10; ++y)
      {
        oval_.getPixel(currPos + x + xOffset, y + yOffset) = text_.getPixel(position + x, y);
      }
    }
    currPos += 14;
  }
  //oval_ now contains vertex with name Image
  stickers_.addSticker(oval_, x1, y1);
}
void LGD::drawVertex(std::string name, unsigned int x1, unsigned int y1)  //overload
{
    //default to black and call drawVertex
    auto color = cs225::HSLAPixel(0,0,0,1);
    drawVertex(name, x1, y1, color);
}

//needs implementation LUCA ALGORITHM HERE!
Image LGD::drawGraph()            
{
  
    
    //BFS->store verts by distance from start->save total nodes # per layer for maxLayerWidth, and save height for maxGraphHegiht
    //loop{}
    //Need these vars:
    //unsgined int maxLayerWidth -- # of verts in widest layer
    //unsinged int maxGraphHeight -- # of layers in tallest part
    //unsigned int totalNodes  -- # of nodes traversed



    //rendering code:

    unsigned int maxLayerWidth = 1;
    unsigned int maxGraphHeight = 1;
    unsigned int totalNodes = 1;
    background_ = Image(); 
    std::string name = "WWWW 987";
    drawVertex(name, 5u, 5u);
    //recursive?
    pic_ = stickers_.render();
    //draw edges
    return pic_;    //replace
}       
Image LGD::drawGraph(Vertex * start)      //overload
{
    start_ = start;
    return drawGraph();
}   
Image LGD::drawGraph(Vertex & start)      //overload
{
    start_ = &start;
    return drawGraph();
}

//partially implemented
//make edge detection to not intersect node?
void LGD::drawEdge(cs225::PNG & png, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel color)
{
  if (x1 == x2)  //handles vertical lines
  {
    //std::cout << "Vertical" << std::endl;
    if (y1 < y2)
    {
      for (; y1 < y2; y1++){png.getPixel(x1,y1) = color;}
    }
    else
    {
       for (; y1 > y2; y1--){png.getPixel(x1,y1) = color;}
    }
    return;
  }
  double slope = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
  //std::cout << "slope = " << slope << std::endl;
  if (slope == 0)     //handles horizontal lines
  {
    //std::cout << "Horiztonal" << std::endl;
    if (x1 < x2)
    {
      for (; x1 < x2; x1++){png.getPixel(x1,y1) = color;}
    }
    else
    {
       for (; x1 > x2; x1--){png.getPixel(x1,y1) = color;}
    }
    return;
  }

  double dy = y1;   //holds absolute position
  
  if (x1 < x2) //east
  {
    if (y1 < y2)//SE
    {
     // std::cout << "SE" << std::endl;
      for (; x1 < x2; x1++)
      {
        dy = dy + slope;
        if ((y1-dy) < 1 && (y1-dy) > -1)
        {
          png.getPixel(x1,y1) = color;
        }
        for (; y1 < dy; y1++)
        {
          //std::cout << "x1 = " << x1 << "   x2 = " << x2 <<"   y1 = " << y1 << "    dy = " << dy << "    y2 = " << y2  << std::endl;
          png.getPixel(x1,y1) = color;
        }
      }
    }
    else        //NE
    {
      //std::cout << "NE" << std::endl;
      for (; x1 < x2; x1++)
      {
        dy = dy + slope;
        if ((y1-dy) < 1 && (y1-dy) > -1)
        {
          png.getPixel(x1,y1) = color;
        }
        for (; y1 > dy; y1--)
        {
          png.getPixel(x1,y1) = color;
        }
      }
    }
  }
  else        //west
  {
    if (y1 < y2)  //SW
    {
      //std::cout << "SW" << std::endl;
      for (; x1 > x2; x1--)
      {
        dy = dy - slope;
        if ((y1-dy) < 1 && (y1-dy) > -1)
        {
          png.getPixel(x1,y1) = color;
        }
        for (; y1 < dy; y1++)
        {
          png.getPixel(x1,y1) = color;
        }
      }
    }
    else          //NW
    {
      
      //std::cout << "NW" << std::endl;
      for (; x1 > x2; x1--)
      {
        dy = dy - slope;
        if ((y1-dy) < 1 && (y1-dy) > -1)
        {
          png.getPixel(x1,y1) = color;
        }
        for (; y1 > dy; y1--)
        {
          png.getPixel(x1,y1) = color;
        }
      }
    }
  }
  return;
}
void LGD::drawEdge(cs225::PNG & png, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) //overload
{
    //default to black and call drawEdge
    auto color = cs225::HSLAPixel(0,0,0,1);
    drawEdge(png, x1, y1, x2, y2, color);
}

