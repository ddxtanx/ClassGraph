#pragma once
#include <cstring>
#include <vector>
#include <fstream>

class DataConvert{
    public:
        static std::vector<std::vector<std::string>> getData(const char* fileName);
};