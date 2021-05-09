#include "SpanningTree.h"
#include <iostream>

SpanningTree::SpanningTree(ClassGraph& other) : Graph(other)
{
    TreeStart=other.getStart();
    BFS traversal(&other, TreeStart);
    for(auto it=traversal.begin();it!=traversal.end();it++)
    {
        Vertex* curr=*it;
        std::cout<<"Adjacents of "<<*curr<<": "<<std::endl;
        std::vector<Vertex*> ADJS=curr->getVerticesPointedTo();
        for(auto it=ADJS.begin();it!=ADJS.end();it++)
        {
            std::cout<<**it;
        }
        std::cout<<std::endl;
    }
}