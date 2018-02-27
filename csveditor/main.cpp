#include "Spreadsheet.hpp"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Fl::option( Fl::OPTION_ARROW_FOCUS, 1 );		// we want arrow keys to navigate table's widgets
    Fl_Double_Window win( 922, 382, "Fl_Table Spreadsheet with Keyboard Navigation" );
    Spreadsheet* table = new Spreadsheet( 20, 20, win.w() - 80, win.h() - 80 );
    table->row_header( 1 );
    table->row_header_width( 70 );
    table->row_resize( 1 );
    table->rows( 11 );
    table->row_height_all( 25 );
    table->col_header( 1 );
    table->col_header_height( 25 );
    table->col_resize( 1 );
    table->cols( 11 );
    table->col_width_all( 70 );
    table->set_selection( 0, 0, 0, 0 );	// select top/left cell

    win.begin();

    // Row slider
    Fl_Value_Slider setrows( win.w() - 40, 20, 20, win.h() - 80, 0 );
    setrows.type( FL_VERT_NICE_SLIDER );
    setrows.bounds( 2, MAX_ROWS );
    setrows.step( 1 );
    setrows.value( table->rows() - 1 );
    setrows.callback( setrows_cb, (void*) table );
    setrows.when( FL_WHEN_CHANGED );
    setrows.clear_visible_focus();

    // Column slider
    Fl_Value_Slider setcols( 20, win.h() - 40, win.w() - 80, 20, 0 );
    setcols.type( FL_HOR_NICE_SLIDER );
    setcols.bounds( 2, MAX_COLS );
    setcols.step( 1 );
    setcols.value( table->cols() - 1 );
    setcols.callback( setcols_cb, (void*) table );
    setcols.when( FL_WHEN_CHANGED );
    setcols.clear_visible_focus();

    win.end();
    win.resizable( table );
    win.show();

    return Fl::run();
}