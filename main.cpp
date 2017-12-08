#include "CSVFile.h"
#include "FileLoader.h"
#pragma warning(push, 0)  
#include "Table.hpp"
#pragma warning(pop)
#include <cassert>
//
// Demonstrate creating a table of widgets without Fl_Table
//                                                   --erco Mar 8 2005

int main( int argc, char** argv )
{
    if (argc < 2)
    {
        return 0;
    }
    std::vector<std::string> file = FileLoader::loadFile( argv[1] );
    CSVFile csvFile;
    csvFile.setDelimeter( "," );
    csvFile.parseContents( file );
    auto isOk = csvFile.checkForCorrectness();
    assert( isOk );

    Fl_Double_Window win( 1024, 600 );
    RateTable rate( 10, 10, 720 - 20, 486 - 20 );
    rate.setData( csvFile.getData() );
    rate.createCells();

    win.resizable( win );
    win.show();
    return(Fl::run());
}