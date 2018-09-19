#include "Spreadsheet.hpp"
#include "CUL/FileFactory.hpp"

int main()
{
    auto file = CUL::FS::FileFactory::createCSVFile( "../media/test.csv" );
    file->load();
    auto csvLinesCount = file->getLinesCount();
    SPRDSHTAPP::Values csvVals;
    for( unsigned i = 0; i < csvLinesCount; ++i )
    {
        SPRDSHTAPP::Row row;
        auto columnCount = file->colsCount();
        for( unsigned j = 0; j < columnCount; ++j )
        {
            auto val = file->getVal( i, j );
            row.push_back( val );
        }
        csvVals.push_back( row );
    }

    auto win = new Fl_Double_Window( 862, 322, "Fl_Table Spreadsheet" );
    auto table = new SPRDSHTAPP::Spreadsheet( 10, 10, win->w() - 20, win->h() - 20, csvVals );
#if FLTK_ABI_VERSION >= 10303
    table->tab_cell_nav( 1 );		// enable tab navigation of table cells (instead of fltk widgets)
#endif
    table->tooltip( "Use keyboard to navigate cells:\n"
                    "Arrow keys or Tab/Shift-Tab" );
    // Table rows
    table->row_header( 1 ); //enable headers
    table->row_header_width( 70 );
    table->row_resize( 1 );
   // table->rows( MAX_ROWS + 1 );// +1: leaves room for 'total row'
    table->row_height_all( 25 );
    // Table cols
    table->col_header( 1 );
    table->col_header_height( 25 );
    table->col_resize( 1 );
    //table->cols( MAX_COLS + 1 );		// +1: leaves room for 'total column'
    table->col_width_all( 70 );

    win->end();
    win->resizable( table );
    win->show();
    return Fl::run();
}