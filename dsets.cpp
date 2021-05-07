#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i = 0; i<num; i++){
        indices_.push_back(-1);
        isElement_.push_back(true);
    }
    largestSize_ = 1;
}

int DisjointSets::find(int n){
    if(n < 0){
        return -1;
    }
    size_t nSize = (size_t) n;
    if(nSize >= indices_.size() || !isElement_[n]){
        return -1;
    }
    int nextIndex = indices_[n];
    if(nextIndex < 0){
        return n;
    } else{
        int correctIndex = find(nextIndex);
        indices_[n] = correctIndex;
        return correctIndex;
    }
}

void DisjointSets::setunion(int a, int b){
    int aIndex = find(a);
    int bIndex = find(b);
    if(aIndex == -1 || bIndex == -1 || (aIndex == bIndex)){
        return;
    }
    int aSize = -indices_[aIndex];
    int bSize = -indices_[bIndex];
    int newSize = -(aSize+bSize);
    int smallIndex;
    int bigIndex;
    if(aSize >= bSize){
        smallIndex = bIndex;
        bigIndex = aIndex;
    } else{
        smallIndex = aIndex;
        bigIndex = bIndex;
    }
    if(largestSize_ < newSize){
        largestSize_ = newSize;
    }
    indices_[smallIndex] = bigIndex;
    indices_[bigIndex] = newSize;
}

int DisjointSets::size(int a){
    int rootIndex = find(a);
    if(rootIndex == -1){
        return 0;
    } else{
        return -indices_[rootIndex];
    }
}

int DisjointSets::getLargestSize(){
    return largestSize_;
}