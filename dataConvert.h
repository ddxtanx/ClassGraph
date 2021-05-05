#pragma once
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

class DataConvert{
    public:
        static std::vector<std::vector<std::string>> getData(const std::string fileName);
        static std::vector<std::string> getDepartments(const std::string filename);
};