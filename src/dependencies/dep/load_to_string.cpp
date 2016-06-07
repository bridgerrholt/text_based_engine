#include "load_to_string.h"

#include <stdexcept>
#include <fstream>

#include "check_file_exists.h"

namespace dep {

std::string
loadToString(com::StringRef fileName)
{
  std::string returnString;

  loadToString(fileName, returnString);

  return returnString;
}



void
loadToString(com::StringRef fileName, 
  std::string& returnString)
{
  if (!checkFileExists(fileName))
    throw std::runtime_error("No such file: " + fileName);

  std::ifstream file(fileName);

  file.seekg(0, std::ios::end);
  returnString.reserve(file.tellg());
  file.seekg(0, std::ios::beg);

  returnString.assign((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}



}