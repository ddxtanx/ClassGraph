#include "LGD.h"
#include <cmath>

// constructors
LGD::LGD() 
: pic_(new PNG()), start_(NULL), graph_(NULL)
{ 
    text_.readFromFile("text.png");
}                      
LGD::LGD(Graph & g, Vertex & v)  
: pic_(new PNG()), start_(&v), graph_(&g)
{
    text_.readFromFile("text.png");
}   
LGD::LGD(Graph * g, Vertex * v)    
: pic_(new PNG()), start_(v), graph_(g)
{
    text_.readFromFile("text.png");
} 
LGD::~LGD()
{   delete pic_;    }
const LGD & LGD::operator= (const LGD & other)
{
    delete pic_;
    pic_ = new PNG(other.pic_); //deep copy PNG
    start_ = other.start_;
    graph_ = other.graph_;
}


void setStart(Vertex * start)
{   start_ = start;     }
void setStart(Vertex & start)
{   start_ = &start;    }


//needs implementation
LGD::drawGraph()            
{
    //BFS->store verts by distance from start->save total nodes # for spacing
    //loop{}
    return NULL;    //replace
}       
LGD::drawGraph(Vertex * start)      //overload
{
    start_ = start;
    return drawGraph();
}   
LGD::drawGraph(Vertex & start)      //overload
{
    start_ = &start;
    return drawGraph();
}

//partially implemented
//make edge detection to not intersect node?
void LGD::drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel & color)
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
void LGD::drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2) //overload
{
    //default to black and call drawEdge
    drawEdge(png, x1, y1, x2, y2, cs225::HSLAPixel color(0,0,0));
}

//needs implementation
void LGD::drawVertex(cs225::PNG & png, unsigned int & x, unsigned int & y, cs225::HSLAPixel & color)
{
    //check dict if dept name has already been made
        //Create a department name PNG from cutting and pasting text.png if not made already
        //place png in dictionary
    //tack on course numbers to department name to get full course name
    //put name on pic_
    //put circle around name in pic_
}
void LGD::drawVertex(cs225::PNG & png, unsigned int & x, unsigned int & y)  //overload
{
    //default to black and call drawVertex
    drawEdge(png, x, y, cs225::HSLAPixel color(0,0,0));
}

