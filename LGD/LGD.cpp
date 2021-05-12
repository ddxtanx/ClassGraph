#include "LGD.h"
#include "../Davids_Work/BFS.h"
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
    skip_.readFromFile("LGD/skip.png");

    //Image pic_();              //sticker output Image, used for edge drawing and final picture
}                      
LGD::LGD(Graph & g, Vertex & v)  
: pic_(Image()), stickers_(new StickerSheet(pic_, 10u)), start_(&v), graph_(&g)
{
    text_.readFromFile("LGD/text.png");
    oval_.readFromFile("LGD/Oval.png");
    skip_.readFromFile("LGD/skip.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
}   
LGD::LGD(Graph * g, Vertex * v)    
: pic_(Image()), stickers_(new StickerSheet(pic_, 10u)), start_(v), graph_(g)
{
    text_.readFromFile("LGD/text.png");
    oval_.readFromFile("LGD/Oval.png");
    skip_.readFromFile("LGD/skip.png");
    //Image pic_();              //sticker output Image, used for edge drawing and final picture
} 
LGD::LGD(const LGD &other)    
: start_(other.start_), graph_(other.graph_)
{
    text_.readFromFile("text.png");
    oval_.readFromFile("oval.png");
    skip_.readFromFile("LGD/skip.png");
    
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

void LGD::makeDummyVerts()
{
    std::vector<Vertex*> vertices=graph_->getVertices();
    for(auto it=vertices.begin();it!=vertices.end();it++)
    {
      Vertex*& currTex=*it;
      if(currTex->getName()=="DUMMY")
      {
        continue;
      }
      std::vector<Vertex*> ADJS=currTex->getVerticesPointedTo();
      int currLayer= (int)currTex->getLayer();
      for(auto iter=ADJS.begin();iter!=ADJS.end();iter++)
      {
        int ADJLayer=(int)(*iter)->getLayer();
        int LayerDiff=ADJLayer-currLayer;
        Vertex*& ADJTex=*iter;
        if(LayerDiff<=1||ADJTex->getName()=="END")
        {
          continue;
        }
        else
        {
          while(LayerDiff>1)
          {
            Vertex* Dummy=new Vertex("DUMMY");
            Dummy->setLayer(currLayer+1);
            currTex->disconnectTo(ADJTex);
            currTex->connectTo(Dummy);
            Dummy->connectTo(ADJTex);
            Dummy->connectFrom(currTex);
            graph_->addVertex(Dummy);
            ADJTex->disconnectFrom(currTex);
            ADJTex->connectFrom(Dummy);
            currTex=Dummy;
            currLayer++;
            graph_->increaseLayerCount(currLayer);
            LayerDiff--;
          }
        }
      }
    }
    //std::cout<<(graph_->getLayerCounts_()).size()<<std::endl;
}


Image LGD::drawGraph()            
{
       
    makeDummyVerts();                                                                       //set up graph with dummy spacers

    std::vector<int> layers = graph_->getLayers();                                          //get whole file layer data
    unsigned int maxLayerWidth = (unsigned int)*max_element(layers.begin(), layers.end());  
    unsigned int maxGraphHeight = layers.size();
    unsigned int totalNodes = (unsigned int)graph_->getVertices().size(); 
    unsigned int currentLayer = 0;                                                          //init counters layer counters
    //rendering code:
    std::cout << "Setting up" << std::endl;
    BFS verts(graph_, start_);                                                              //BFS used to traverse data
    unsigned int minLayer = start_->getLayer();

    //subgraph sizing code:
    if (start_->getName() != "START")                                                       //If custom course specified, size down Image
    {                                                                                       //by traversing and storing sub-graph layer data
      std::cout << "Drawing sub-graph" << std::endl;
      unsigned maxLayer = minLayer;
      std::vector<unsigned int> subLayers;
      subLayers.resize((size_t)maxGraphHeight);
      unsigned nodeCounter = 0;
      for (auto it = verts.begin(); it != verts.end(); ++it)                                //use BFS to create a smaller Image bounds
      {
        currentLayer = (*it)->getLayer();
        if (currentLayer > maxLayer)
          maxLayer = currentLayer;
        ++subLayers[currentLayer-minLayer];
        ++nodeCounter;
      }
      maxLayerWidth = (unsigned int)*max_element(subLayers.begin(), subLayers.end());  
      maxGraphHeight = maxLayer - minLayer;
      totalNodes = nodeCounter;
    }

    std::cout << "Height of graph (# of verts): " << maxGraphHeight << std::endl;
    std::cout << "Width of graph  (# of verts): " << maxLayerWidth << std::endl;
    std::cout <<  std::endl;
    
    Image temp(150*maxLayerWidth, 250*maxGraphHeight);                        //creates image to use as background
    background_ = temp;    
    stickers_ = new StickerSheet(background_,totalNodes);                     //make sticker sheet to render vertices

    
    currentLayer = 0;                                                          //init counters layer counters
    //unsigned int x = 0;
    std::vector<unsigned int> layerCount;
    layerCount.resize(layers.size());
    std::cout<<background_.width()<<std::endl;
    std::vector<int> Spacings;
    for(unsigned i=0;i<layers.size();i++)
    {
      std::cout<<"Layer: "<<i<<" Number of verts: "<<layers[i]<<std::endl;
      int layerSpacing=background_.width()/(layers[i]+1);
      std::cout<<"Layer: "<<i<<" Spacing "<<layerSpacing<<std::endl;
      Spacings.push_back(layerSpacing);
    }

    std::cout << "Making verts into Stickers" << std::endl;
    for (auto it = verts.begin(); it != verts.end(); ++it)
    {
      currentLayer = (*it)->getLayer();
      (*it)->xPos = (layerCount[currentLayer]+1)*Spacings[currentLayer];
      (*it)->yPos = (currentLayer-minLayer)*250;
      if (!detectEND(*it))                //prevents drawing
        drawVertex(*it, (*it)->xPos, (*it)->yPos);
      ++layerCount[currentLayer];
      //++x;
    }


    std::cout << "Calling Render on StickerSheet" << std::endl;
    pic_ = stickers_->render(); //render vertices


    std::cout << "Drawing Edges onto pic_" << std::endl;
    std::vector<Vertex*> adj;
    for (auto it = verts.begin(); it != verts.end(); ++it)    //loops through all verts via BFS, *it is the lower vertex, this draws down from start
    {
      adj = (*it)->getVerticesPointedTo();
      if ((*it)->getName() == "START")            //skip start node
        continue;
      for (auto at = adj.begin(); at != adj.end(); ++at)      //loops through adjacent verts to *it
      {
        if (detectEND(*at))                //prevents drawing
          continue;
        drawEdge(*it, *at);
      }
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
void LGD::drawEdge(Vertex * v1, Vertex * v2) //overload
{
  unsigned int x1 = v1->xPos;
  unsigned int y1 = v1->yPos;
  unsigned int x2 = v2->xPos;
  unsigned int y2 = v2->yPos;
  drawEdge(x1, y1, x2, y2, cs225::HSLAPixel(0,0,0));
}
void LGD::drawEdge(Vertex & v1, Vertex & v2) //overload
{
  unsigned int x1 = v1.xPos;
  unsigned int y1 = v1.yPos;
  unsigned int x2 = v2.xPos;
  unsigned int y2 = v2.yPos;
  drawEdge(x1, y1, x2, y2, cs225::HSLAPixel(0,0,0));
}

//needs testing //hogs memory
int LGD::drawVertex(std::string name , unsigned int x1, unsigned int y1, cs225::HSLAPixel color)
{
  unsigned int xOffset = 14;
  unsigned int yOffset = 10;
  unsigned int currPos = 0;
  unsigned int position = 0;
  unsigned int xLim = 14;


  if (name == "DUMMY")
  {
    //std::cout << "drawing dummy" << std::endl;
    return stickers_->addSticker(skip_, x1, y1);
  }

  //std::cout << "name: " << name << std::endl;
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
    return drawVertex(v->getName(), v->xPos, y1, cs225::HSLAPixel(0,0,0));
}
int LGD::drawVertex(Vertex & v, unsigned int x1, unsigned int y1)  //overload
{
    //default to black and call drawVertex
    return drawVertex(v.getName(), v.xPos, y1, cs225::HSLAPixel(0,0,0));
}

bool LGD::detectEND(Vertex * v) //recursive checker to see if END node is at the end of a string of DUMMYs
{

  std::string name = v->getName();
  if (name == "END")
    return true;
  else if (name == "DUMMY")
    return detectEND(v->getVerticesPointedTo()[0]);
  else
    return false;
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


//        TEST DRAW VERT + EDGE



    /*
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
    */





//



//saving draw edges up code
   /*
   
    for (auto it = verts.begin(); it != verts.end(); ++it)
    {
      adj = (*it)->getVerticesPointedFrom();

      if ((*it)->getName() == "END")            //skip start node when printing whole departments
        continue;

      for (auto at = adj.begin(); at != adj.end(); ++at)
      {
        if ((*at)->getName() == "START")
          continue;

        drawEdge(*at, *it);
      }
    }

   */