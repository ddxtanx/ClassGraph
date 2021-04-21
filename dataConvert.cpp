#include <fstream>
using std::ifstream;

#include <cstring>
#include <vector>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = ",";

std::vector<std::vector<std::string>> getData(const char* fileName)
{
  std::vector<std::vector<std::string>> tokens;
  ifstream fin;
  fin.open(fileName); // open a file
  if (!fin.good())
  { 
    std::cout<<"FAILED TO OPEN FILE"<<std::endl;
    return tokens; // exit if file not found
  }
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);

    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index

    // Vector to store memory addresses of the tokens in buf
    std::vector<std::string> token;
    //Parse the line.
    char* first=strtok(buf, DELIMITER);//Get first token
    token.push_back(std::string(first));
    if(first)
    {
        for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        char* currTok = (strtok(0, DELIMITER)); // subsequent tokens
        if (!currTok) break; // no more tokens
        token.push_back(std::string(currTok));//If token is not null, add it to the token vector
      }
    }
    tokens.push_back(token); //Push the current token to the vector of tokens.
  }
  return tokens;
}