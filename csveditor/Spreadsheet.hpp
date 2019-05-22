#pragma once
#ifdef _MSC_VER
__pragma( warning( push ) ) \
__pragma( warning( disable:4244 ) )
__pragma( warning( disable:4458 ) )
__pragma( warning( disable:4100 ) )
#endif
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

using Columns = std::vector<std::string>;
using Rows = std::vector <Columns>;
class Spreadsheet final: public Fl_Table
{
public:
    Spreadsheet(
        int X, int Y,
        int W, int H, const char* L = 0 );
    ~Spreadsheet();

    void set_value_hide();
    void rows( int val );
    void cols( int val );
    inline int rows();
    inline int cols();
    void start_editing( int R, int C );
    void done_editing();

protected:
    void draw_cell( TableContext context, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0 );
    void tableEvent();
    static void event_callback( Fl_Widget*, void *v );
    static void input_cb( Fl_Widget*, void* v );

private:
    const double getVal( int r, int c );

    Fl_Int_Input* m_input = nullptr;
    Rows values;
    int row_edit, col_edit;
    int s_left, s_top, s_right, s_bottom;

};

void setrows_cb( Fl_Widget* w, void* v );
void setcols_cb( Fl_Widget* w, void* v );