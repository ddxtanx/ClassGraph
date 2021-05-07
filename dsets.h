/* Your code here! */
#pragma once
#include <vector>
class DisjointSets{
    public:
        void addelements(int num);
        int find(int k);
        void setunion(int a, int b);
        int size(int elem);
        int getLargestSize();
    private:
        std::vector<int> indices_;
        std::vector<bool> isElement_;
        int largestSize_;
};