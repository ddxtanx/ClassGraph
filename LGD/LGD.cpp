#include "LGD.h"
#include "../cs225/PNG.h"
#include "../Stickers/Image.h"
#include <cmath>

using namespace cs225;
// constructors, rule of 3
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

  void LGD::setStart(Vertex * start)
  {   start_ = start;     }
  void LGD::setStart(Vertex & start)
  {   start_ = &start;    }
*/


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
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "++++++++++++ DISCLAIMER ++++++++++++" << std::endl;
    std::cout << "The current drawGraph() meathod" << std::endl;
    std::cout << "simply draws all verts in the" << std::endl;
    std::cout << "order they are stored in the" << std::endl;
    std::cout << "graph obj, and lines are drawn" << std::endl;
    std::cout << "between consecutive vertexes." < std::endl;
    std::cout << "This is debug, not final, behavior" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++" < std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    unsigned int maxLayerWidth;
    unsigned int maxGraphHeight;


    std::vector<Vertex*> & verts = graph_->getVertices();
    size_t size = verts.size();
    maxLayerWidth = 2;
    while (maxLayerWidth*maxLayerWidth < size)
    {
      ++maxLayerWidth;
    }
    maxGraphHeight = maxLayerWidth;


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


    std::cout << "Calling Render" << std::endl;
    pic_ = stickers_->render(); //render vertices

    std::cout << "Drawing Edges" << std::endl;
    unsigned int idx = 0;
    Image * curr = NULL;
    Image * prev = NULL;
    while ( (curr = stickers_->getSticker(idx)) != NULL)
    {
      if (prev == NULL)
      {
        prev = curr;
        ++idx;
        continue;
      }
      drawEdge(prev, curr);
      prev = curr;
      ++idx;
    }

    std::cout << "Returning pic_" << std::endl;
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
void LGD::drawEdge(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel color)
{
  unsigned int xCenter = 63;
  unsigned int yBottom = 31;
  x1 += xCenter;
  x2 += xCenter;
  y1 += yBottom;


  //####################### Code from David's mp_intro ##############################

  if (x1 == x2)  //handles vertical lines
  {
    //std::cout << "Vertical" << std::endl;
    if (y1 < y2)
    {
      for (; y1 < y2; y1++){pic_.getPixel(x1,y1) = color;}
    }
    else
    {
       for (; y1 > y2; y1--){pic_.getPixel(x1,y1) = color;}
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
      for (; x1 < x2; x1++){pic_.getPixel(x1,y1) = color;}
    }
    else
    {
       for (; x1 > x2; x1--){pic_.getPixel(x1,y1) = color;}
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
          pic_.getPixel(x1,y1) = color;
        }
        for (; y1 < dy; y1++)
        {
          //std::cout << "x1 = " << x1 << "   x2 = " << x2 <<"   y1 = " << y1 << "    dy = " << dy << "    y2 = " << y2  << std::endl;
          pic_.getPixel(x1,y1) = color;
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
          pic_.getPixel(x1,y1) = color;
        }
        for (; y1 > dy; y1--)
        {
          pic_.getPixel(x1,y1) = color;
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
          pic_.getPixel(x1,y1) = color;
        }
        for (; y1 < dy; y1++)
        {
          pic_.getPixel(x1,y1) = color;
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
          pic_.getPixel(x1,y1) = color;
        }
        for (; y1 > dy; y1--)
        {
          pic_.getPixel(x1,y1) = color;
        }
      }
    }
  }
  return;
}
void LGD::drawEdge(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) //overload
{
    drawEdge(x1, y1, x2, y2, cs225::HSLAPixel(0,0,0));
}
void LGD::drawEdge(Image * pic1, Image * pic2) //overload
{
    unsigned int x1 = pic1->xPos;
    unsigned int y1 = pic1->yPos;
    unsigned int x2 = pic2->xPos;
    unsigned int y2 = pic2->yPos;
    drawEdge(x1, y1, x2, y2, cs225::HSLAPixel(0,0,0));
}
void LGD::drawEdge(Image & pic1, Image & pic2) //overload
{
    unsigned int x1 = pic1.xPos;
    unsigned int y1 = pic1.yPos;
    unsigned int x2 = pic2.xPos;
    unsigned int y2 = pic2.yPos;
    drawEdge(x1, y1, x2, y2, cs225::HSLAPixel(0,0,0));
}

//needs testing //hogs memory
int LGD::drawVertex(std::string name , unsigned int x1, unsigned int y1, cs225::HSLAPixel color)
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
  return stickers_->addSticker(drawing, x1, y1);
}
int LGD::drawVertex(std::string  name, unsigned int x1, unsigned int y1)  //overload
{
    //default to black and call drawVertex
    return drawVertex(name, x1, y1, cs225::HSLAPixel(0,0,0));
}
int LGD::drawVertex(Vertex* v, unsigned int x1, unsigned int y1)  //overload
{
    //default to black and call drawVertex
    return drawVertex(v->getName(), x1, y1, cs225::HSLAPixel(0,0,0));
}
int LGD::drawVertex(Vertex & v, unsigned int x1, unsigned int y1)  //overload
{
    //default to black and call drawVertex
    return drawVertex(v.getName(), x1, y1, cs225::HSLAPixel(0,0,0));
}




////////// Debug material //////////

//test vertex drawing
/* --project.cpp
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Testing draw Vertex" << std::endl;

  std::cout << "Creating LGD obj with graph g and START" << std::endl;
  LGD l(&g, start);
  std::cout << "Calling DrawGraph" << std::endl;
  Image output = l.drawGraph();
  std::cout << "Writing to File" << std::endl;
  output.writeToFile("Output_PNGs/myImage.png");
*/