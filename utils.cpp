#include <string>
#include "utils.h"
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const std::vector<std::string> depts = {"AAS","ABE","ACCY","ACE","ACES","ADV","AE","AFAS","AFRO","AFST","AGCM","AGED","AHS","AIS","ANSC","ANTH","ARAB","ARCH","ART","ARTD","ARTE","ARTF","ARTH","ARTS","ASRM","ASST","ASTR","ATMS","BADM","BASQ","BCOG","BCS","BIOC","BIOE","BIOP","BSE","BTW","BUS","CB","CDB","CEE","CHBE","CHEM","CHIN","CHLH","CHP","CI","CIC","CLCV","CLE","CMN","CPSC","CS","CSE","CW","CWL","CZCH","DANC","EALC","ECE","ECON","EDPR","EDUC","EIL","ENG","ENGH","ENGL","ENSU","ENVS","EOL","EPOL","EPS","EPSY","ESE","ESL","EURO","FAA","FIN","FLTE","FR","FSHN","GC","GCL","GEOG","GEOL","GER","GLBL","GMC","GRK","GRKM","GS","GWS","HDFS","HEBR","HIST","HNDI","HORT","HRD","HUM","IB","IE","IHLT","INFO","IS","ITAL","JAPN","JOUR","JS","KIN","KOR","LA","LAS","LAST","LAT","LAW","LER","LING","LLS","MACS","MATH","MBA","MCB","MDIA","MDVL","ME","MICR","MILS","MIP","MSE","MUS","MUSE","NEUR","NPRE","NRES","NS","NUTR","PATH","PERS","PHIL","PHYS","PLPA","POL","PORT","PS","PSM","PSYC","REES","REHB","REL","RHET","RSOC","RST","RUSS","SAME","SBC","SCAN","SE","SHS","SLAV","SLS","SOC","SOCW","SPAN","SPED","STAT","SWAH","TAM","TE","THEA","TMGT","TRST","TSM","TURK","UKR","UP","VCM","VM","WLOF","WRIT","YDSH","ZULU"};
int Utils::numDepts = depts.size();
std::unordered_map<std::string, int> deptNumMap;
bool mapInitialized = false;

int getDeptNum(std::string department){
    if(!mapInitialized){
        int i = 0;
        for(std::string dept: depts){
            deptNumMap[dept] = i;
            i++;
        }
        mapInitialized = true;
    }
    return deptNumMap[department];
}
int Utils::hashCourseName(std::string courseName){
    std::regex classRegex("(AAS|ABE|ACCY|ACE|ACES|ADV|AE|AFAS|AFRO|AFST|AGCM|AGED|AHS|AIS|ANSC|ANTH|ARAB|ARCH|ART|ARTD|ARTE|ARTF|ARTH|ARTS|ASRM|ASST|ASTR|ATMS|BADM|BASQ|BCOG|BCS|BIOC|BIOE|BIOP|BSE|BTW|BUS|CB|CDB|CEE|CHBE|CHEM|CHIN|CHLH|CHP|CI|CIC|CLCV|CLE|CMN|CPSC|CS|CSE|CW|CWL|CZCH|DANC|EALC|ECE|ECON|EDPR|EDUC|EIL|ENG|ENGH|ENGL|ENSU|ENVS|EOL|EPOL|EPS|EPSY|ESE|ESL|EURO|FAA|FIN|FLTE|FR|FSHN|GC|GCL|GEOG|GEOL|GER|GLBL|GMC|GRK|GRKM|GS|GWS|HDFS|HEBR|HIST|HNDI|HORT|HRD|HUM|IB|IE|IHLT|INFO|IS|ITAL|JAPN|JOUR|JS|KIN|KOR|LA|LAS|LAST|LAT|LAW|LER|LING|LLS|MACS|MATH|MBA|MCB|MDIA|MDVL|ME|MICR|MILS|MIP|MSE|MUS|MUSE|NEUR|NPRE|NRES|NS|NUTR|PATH|PERS|PHIL|PHYS|PLPA|POL|PORT|PS|PSM|PSYC|REES|REHB|REL|RHET|RSOC|RST|RUSS|SAME|SBC|SCAN|SE|SHS|SLAV|SLS|SOC|SOCW|SPAN|SPED|STAT|SWAH|TAM|TE|THEA|TMGT|TRST|TSM|TURK|UKR|UP|VCM|VM|WLOF|WRIT|YDSH|ZULU) ([0-7][0-9]{2})");
    std::smatch matches;
    if(std::regex_match(courseName, matches, classRegex)){
        std::string dept = matches[1].str();
        std::string numStr = matches[2].str();
        int num = std::stoi(numStr);
        int thousandsMult = getDeptNum(dept);
        return thousandsMult*800+num;
    }
    std::cout << "Class does not fit regex: " << courseName << std::endl; 
    return -1;
}

const std::string whiteSpaces( " \f\n\r\t\v" );


void Utils::trimRight(std::string& str)
{
   std::string::size_type pos = str.find_last_not_of( whiteSpaces );
   str.erase( pos + 1 );    
}


void Utils::trimLeft( std::string& str)
{
   std::string::size_type pos = str.find_first_not_of( whiteSpaces );
   str.erase( 0, pos );
}


void Utils::trim( std::string& str)
{
   trimRight(str);
   trimLeft(str);
} 