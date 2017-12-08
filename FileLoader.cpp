#include "FileLoader.h"
#include <fstream>
#include <vector>

const std::vector<std::string> FileLoader::loadFile( const std::string& filePath )
{
    std::vector<std::string> result;

    std::string line;
    std::ifstream myfile( filePath );
    if( myfile.is_open() )
    {
        while( getline( myfile, line ) )
        {
            result.push_back( line );
        }
        myfile.close();
    }
    return result;
}