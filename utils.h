#pragma once

#include <string>
#include <vector>
#include <unordered_map>
class Utils{
    public:
        static int hashCourseName(std::string courseName);
        static void initializeDepts(std::string fileName);
        static void trimRight(std::string& str);
        static void trimLeft(std::string& str);
        static void trim(std::string& str);
        static int numDepts;
    private:
        static int getDeptNum(std::string deptName);
        static bool deptsInitialized;
        static bool mapInitialized;
        static std::vector<std::string> depts;
        static std::string courseRegexStr;
        static std::unordered_map<std::string, int> deptNumMap;
        static std::string currentInitializedFilename;
};