#pragma once
#include <string>
#include <vector>
class FileLoader
{
public:
    static const std::vector<std::string> loadFile( const std::string& filePath );
};