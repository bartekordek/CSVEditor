#pragma once
#ifdef _MSC_VER
__pragma( warning( push ) ) \
__pragma( warning( disable:4244 ) )
__pragma( warning( disable:4458 ) )
__pragma( warning( disable:4100 ) )
#endif
#include "CUL/Math/PosTable.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/fl_draw.H>
#ifdef _MSC_VER
__pragma( warning( pop ) )
#endif

#include <string>
#include <vector>

const int MAX_COLS = 26;
const int MAX_ROWS = 500;

NAMESPACE_BEGIN( SPRDSHTAPP )
using Row = std::vector<std::string>;
using TablePos = CUL::Math::PosTableU;
class Spreadsheet final:
    public Fl_Table
{
public:
    Spreadsheet( int X, int Y, int W, int H, const char* L = 0 );
    ~Spreadsheet();

    struct CartPos
    {
        unsigned x = 0;
        unsigned y = 0;
    };

protected:
    void draw_cell(
        TableContext context,
        int R = 0, int C = 0,
        int X = 0, int Y = 0,
        int W = 0, int H = 0 ) override;
    void event_callback2();// table's event callback (instance)
    static void event_callback( Fl_Widget*, void *v );
    static void input_cb( Fl_Widget*, void* v );

private:
    void setValueHide();
    void doneEditing();
    void startEditing( int R, int C );
    double sumRows( int C );// Return the sum of all rows in this column
    double sumCols( int R );// Return the sum of all cols in this row
    double sumAll();// Return the sum of all cells in table
    void drawCell( const std::string& val, const CartPos& position );

    Fl_Int_Input* input = nullptr;

    std::vector<Row> m_values;
    TablePos m_currentCellInfo;
};
NAMESPACE_END( SPRDSHTAPP )