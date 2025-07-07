#ifndef FILEINTERACT_H_INCLUDED
#define FILEINTERACT_H_INCLUDED

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

const std::vector<std::string> getFilenamesWithoutExtension(const std::string& path);
std::string readFileToString(const std::string& filePath);

#endif //