#include "LGD.h"
#define ROOT3 1.732050808

// constructors
LGD::LGD() 
: pic_(new PNG()), start_(NULL), graph_(NULL)
{}                      
LGD::LGD(Graph & g, Vertex & v)  
: pic_(new PNG()), start_(&g), graph_(&v)
{}   
LGD::LGD(Graph * g, Vertex * v)    
: pic_(new PNG()), start_(g), graph_(v)
{} 


LGD::drawGraph()            
{


    return NULL;    //replace

}       
LGD::drawGraph(Vertex * start)   
{
    start_ = start;
    return drawGraph();
}   
LGD::drawGraph(Vertex & start)
{
    start_ = &start;
    return drawGraph();
}
void drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel & color)
{
    //default to black and call drawEdge
}




void drawEdge(cs225::PNG & png, unsigned int & x1, unsigned int & y1, unsigned int x2, unsigned int y2, cs225::HSLAPixel & color)
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
  

  if (x1 < x2)
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
  else
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