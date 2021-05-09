#include "LGD.h"
#include "../cs225/PNG.h"
#include "../Stickers/Image.h"
#include <cmath>

using namespace cs225;
// constructors
LGD::LGD() 
: pic_(Image()), stickers_(new StickerSheet(pic_, 10u)), start_(NULL),  graph_(NULL)
{ 
    text_.readFromFile("LGD/text.png");
    oval_.readFromFile("LGD/Oval.png");

    //Image pic_();              //sticker output Image, used for edge drawing and final picture
}                      
LGD::LGD(Graph & g, Vertex & v)  
: pic_(Image()), stickers_(new StickerSheet(pic_, 10u)), start_(&v), graph_(&g)
{
    text_.readFromFile("LGD/text.png");
    oval_.readFromFile("LGD/Oval.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
}   
LGD::LGD(Graph * g, Vertex * v)    
: pic_(Image()), stickers_(new StickerSheet(pic_, 10u)), start_(v), graph_(g)
{
    text_.readFromFile("LGD/text.png");
    oval_.readFromFile("LGD/Oval.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
} 
LGD::LGD(const LGD &other)    
: start_(other.start_), graph_(other.graph_)
{
    text_.readFromFile("text.png");
    oval_.readFromFile("oval.png");
    
    pic_ = other.pic_;
    background_ = other.background_;
    if (other.stickers_ != NULL)
    {
      stickers_ = new StickerSheet(*other.stickers_);
    }
    else
    {
      stickers_ = NULL;
    }
} 


LGD::~LGD()
{   
  delete stickers_;   
  stickers_ = NULL; 
}
const LGD & LGD::operator= (const LGD & other)
{
    
    if (other.stickers_ != NULL)
    {
      delete stickers_;
      stickers_ = new StickerSheet(*other.stickers_);
    }
    else
    {
      stickers_ = NULL;
    }
    pic_ = other.pic_;
    background_ = other.background_;
    start_ = other.start_;
    graph_ = other.graph_;
    return *this;
}

/*
void setStart(Vertex * s)
{   start_ = s;     }
void setStart(Vertex & s)
{   start_ = &s;    }
*/
void LGD::setStart(Vertex * start)
{   start_ = start;     }
void LGD::setStart(Vertex & start)
{   start_ = &start;    }



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
    
    unsigned int maxLayerWidth;
    unsigned int maxGraphHeight;

    //####### Temp code that just plots all vertices in a sqaure png ##############
    std::vector<Vertex*> & verts = graph_->getVertices();
    size_t size = verts.size();
    maxLayerWidth = 2;
    while (maxLayerWidth*maxLayerWidth < size)
    {
      ++maxLayerWidth;
    }
    maxGraphHeight = maxLayerWidth;
    //#############################################################################




    unsigned int totalNodes = (unsigned int)size;
    Image temp(150*maxLayerWidth, 50*maxGraphHeight);
    background_ = temp;
    
    stickers_ = new StickerSheet(background_,totalNodes); //make sticker sheet to render vertices

    std::vector<Vertex*>::iterator it = verts.begin();


    for (unsigned int x = 0; x < maxLayerWidth; ++x)
    {
      for (unsigned int y = 0; y < maxGraphHeight; ++y)
      {
        if (it == verts.end())
          break;
        drawVertex((*it)->getName(), x*150, y*50);
        ++it;
      }
    }

    


    //recursive meathod??
    std::cout << "Calling Render" << std::endl;
    pic_ = stickers_->render(); //render vertices

    //draw edges TODO

    return pic_;    //returning graph result

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
    drawEdge(png, x1, y1, x2, y2, cs225::HSLAPixel(0,0,0));
}

//needs testing
void LGD::drawVertex(std::string name , unsigned int x1, unsigned int y1, cs225::HSLAPixel color)
{
    //check dict if dept name has already been made
    //Create a department name PNG from cutting and pasting text.png if not made already
    //place png in dictionary

  unsigned int xOffset = 14;
  unsigned int yOffset = 10;
  unsigned int currPos = 0;
  unsigned int position = 0;
  unsigned int xLim = 14;

  Image drawing(oval_);
  for (char& c : name)
  {
    if (currPos > 90)
      break;
    if (c - ' ' == 0)
    {
      currPos = 63; //if space is encountered, set the spacing to be consistant
      continue;     
    }
    else if (c - '0' < 10)                        //if number is encountered
    {
      position = 14*(26 + (unsigned int)(c-'0')); //gets position of character in text.png
      xLim = 11;
    }
    else if (c - 'A' >= 0)                         //if letter is encountered
    {
      position = 14*(unsigned int)(c-'A');        //gets position of character in text.png
      xLim = 14;
    }

    //copies letter from text.png to oval.png, overwriting any past vertex
    for (unsigned int x = 0; x < xLim; ++x)
    {
      for (unsigned int y = 0; y < 10; ++y)
      {
        drawing.getPixel(currPos + x + xOffset, y + yOffset) = text_.getPixel(position + x, y);
      }
    }
    currPos += xLim;
  }
  //oval_ now contains vertex with name Image
  stickers_->addSticker(drawing, x1, y1);
}
void LGD::drawVertex(std::string  name, unsigned int x1, unsigned int y1)  //overload
{
    //default to black and call drawVertex
    drawVertex(name, x1, y1, cs225::HSLAPixel(0,0,0));
}

