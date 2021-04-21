#include "Vertex.h"
size_t Vertex::count = 0;
Vertex::Vertex(){
    name_ = "";
    id_ = count;
    count++;
}