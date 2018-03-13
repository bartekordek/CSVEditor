#include "Spreadsheet.hpp"

Spreadsheet::Spreadsheet(
    int X, int Y,
    int W, int H, const char* L ):
    Fl_Table( X, Y, W, H, L )
{
    this->values.resize( MAX_ROWS );
    for( auto& row: this->values )
    {
        row.resize( MAX_COLS );
    }

    callback( &event_callback, (void*) this );
    when( static_cast<uchar>( FL_WHEN_NOT_CHANGED | when() ) );
    input = new Fl_Int_Input( W / 2, H / 2, 0, 0 );
    input->hide();
    input->callback( input_cb, (void*) this );
    input->when( FL_WHEN_ENTER_KEY_ALWAYS );
    input->maximum_size( 5 );
    row_edit = col_edit = 0;
    s_left = s_top = s_right = s_bottom = 0;
    for( int c = 0; c < MAX_COLS; c++ )
        for( int r = 0; r < MAX_ROWS; r++ )
            this->values[ r ][ c ] = std::to_string( ( r + 2 ) * ( c + 3 ) );
    end();
}

Spreadsheet::~Spreadsheet()
{
    delete this->input;
}

void Spreadsheet::set_value_hide()
{
    values[ row_edit ][ col_edit ] = input->value();
    input->hide();
    window()->cursor( FL_CURSOR_DEFAULT );
}

void Spreadsheet::rows( int val )
{
    Fl_Table::rows( val );
}

void Spreadsheet::cols( int val )
{
    Fl_Table::cols( val );
}

inline int Spreadsheet::rows()
{
    return Fl_Table::rows();
}

inline int Spreadsheet::cols()
{
    return Fl_Table::cols();
}

void Spreadsheet::start_editing( int R, int C )
{
    row_edit = R;
    col_edit = C;
    int X, Y, W, H;
    find_cell( CONTEXT_CELL, R, C, X, Y, W, H );
    input->resize( X, Y, W, H );
    input->value( values[ R ][ C ].c_str() );
    input->position( 0, static_cast<int>( strlen( values[ R ][ C ].c_str() ) ) );
    input->show();
    input->take_focus();
}

void Spreadsheet::done_editing()
{
    if( input->visible() )
    {
        set_value_hide();
    }
}

const double Spreadsheet::sum_rows( int C )
{
    double sum = 0.0;
    for( int r = 0; r < rows() - 1; ++r )			// -1: don't include cell data in 'totals' column
        sum += getVal( r, C );
    return( sum );
}

const double Spreadsheet::sum_cols( int R )
{
    double sum = 0.0;
    for( int c = 0; c<cols() - 1; ++c )			// -1: don't include cell data in 'totals' column
        sum += getVal( R, c );
    return sum ;
}

const double Spreadsheet::sum_all()
{
    double sum = 0.0;
    for( int c = 0; c<cols() - 1; ++c )			// -1: don't include cell data in 'totals' column
        for( int r = 0; r<rows() - 1; ++r )			// -1: ""
            sum += getVal( r, c );
    return sum ;
}

void Spreadsheet::draw_cell( TableContext context, int R, int C, int X, int Y, int W, int H )
{
    static char stext[ 30 ];
    switch( context )
    {
    case CONTEXT_STARTPAGE:			// table about to redraw
        get_selection( s_top, s_left, s_bottom, s_right );
        break;

    case CONTEXT_COL_HEADER:			// table wants us to draw a column heading (C is column)
        fl_font( FL_HELVETICA | FL_BOLD, 14 );	// set font for heading to bold
        fl_push_clip( X, Y, W, H );			// clip region for text

        fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, col_header_color() );
        fl_color( FL_BLACK );
        if( C == cols() - 1 )
        {			// Last column? show 'TOTAL'
            fl_draw( "TOTAL", X, Y, W, H, FL_ALIGN_CENTER );
        }
        else
        {				// Not last column? show column letter
            sprintf( stext, "%c", 'A'  );
            fl_draw( stext, X, Y, W, H, FL_ALIGN_CENTER );
        }

        fl_pop_clip();
        return;

    case CONTEXT_ROW_HEADER:			// table wants us to draw a row heading (R is row)
        fl_font( FL_HELVETICA | FL_BOLD, 14 );	// set font for row heading to bold
        fl_push_clip( X, Y, W, H );

        fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, row_header_color() );
        fl_color( FL_BLACK );
        if( R == rows() - 1 )
        {			// Last row? Show 'Total'
            fl_draw( "TOTAL", X, Y, W, H, FL_ALIGN_CENTER );
        }
        else
        {				// Not last row? show row#
            sprintf( stext, "%d", R + 1 );
            fl_draw( stext, X, Y, W, H, FL_ALIGN_CENTER );
        }

        fl_pop_clip();
        return;

    case CONTEXT_CELL:
    {			// table wants us to draw a cell
        if( R == row_edit && C == col_edit && input->visible() )
        {
            return;					// dont draw for cell with input widget over it
        }
        if( R >= s_top && R <= s_bottom && C >= s_left && C <= s_right )
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, FL_YELLOW );
        }
        else if( C < cols() - 1 && R < rows() - 1 )
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, FL_WHITE );
        }
        else
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, 0xbbddbb00 );	// money green
        }
        // Text
        fl_push_clip( X + 3, Y + 3, W - 6, H - 6 );

        fl_color( FL_BLACK );
        if( C == cols() - 1 || R == rows() - 1 )
        {	// Last row or col? Show total
            fl_font( FL_HELVETICA | FL_BOLD, 14 );	// ..in bold font
            std::string valueAsString;
            if( C == cols() - 1 && R == rows() - 1 )
            {	// Last row+col? Total all cells
                valueAsString = std::to_string( sum_all() );
            }
            else if( C == cols() - 1 )
            {		// Row subtotal
                valueAsString = std::to_string( sum_cols( R ) );
            }
            else if( R == rows() - 1 )
            {		// Col subtotal
                valueAsString = std::to_string( sum_rows( C ) );
            }
            fl_draw( valueAsString.c_str(), X + 3, Y + 3, W - 6, H - 6, FL_ALIGN_RIGHT );
        }
        else
        {				// Not last row or col? Show cell contents
            fl_font( FL_HELVETICA, 14 );		// ..in regular font
            fl_draw( values[ R ][ C ].c_str(), X + 3, Y + 3, W - 6, H - 6, FL_ALIGN_RIGHT );
        }

        fl_pop_clip();
        return;
    }

    case CONTEXT_RC_RESIZE:
    {			// table resizing rows or columns
        if( !input->visible() ) return;
        find_cell( CONTEXT_TABLE, row_edit, col_edit, X, Y, W, H );
        if( X == input->x() && Y == input->y() && W == input->w() && H == input->h() )
        {
            return;					// no change? ignore
        }
        input->resize( X, Y, W, H );
        return;
    }

    default:
        return;
    }
}

// Callback whenever someone clicks on different parts of the table
void Spreadsheet::tableEvent()
{
    int R = callback_row();
    int C = callback_col();
    TableContext context = callback_context();

    switch( context )
    {
    case CONTEXT_CELL:
    {				// A table event occurred on a cell
        switch( Fl::event() )
        { 				// see what FLTK event caused it
        case FL_PUSH:					// mouse click?
            done_editing();				// finish editing previous
            if( R != rows() - 1 && C != cols() - 1 )		// only edit cells not in total's columns
                start_editing( R, C );				// start new edit
            return;

        case FL_KEYBOARD:				// key press in table?
            if( Fl::event_key() == FL_Escape ) exit( 0 );	// ESC closes app
            if( C == cols() - 1 || R == rows() - 1 ) return;	// no editing of totals column
            done_editing();				// finish any previous editing
            set_selection( R, C, R, C );			// select the current cell
            start_editing( R, C );				// start new edit
            if( Fl::event() == FL_KEYBOARD && Fl::e_text[ 0 ] != '\r' )
            {
                input->handle( Fl::event() );			// pass keypress to input widget
            }
            return;
        }
        return;
    }

    case CONTEXT_TABLE:					// A table event occurred on dead zone in table
    case CONTEXT_ROW_HEADER:				// A table event occurred on row/column header
    case CONTEXT_COL_HEADER:
        done_editing();					// done editing, hide
        return;

    default:
        return;
    }
}

void setrows_cb( Fl_Widget* w, void* v )
{
    Spreadsheet* table = (Spreadsheet*) v;
    Fl_Valuator* in = (Fl_Valuator*) w;
    int rows = int( in->value() ) + 1;
    table->rows( rows );
    table->redraw();
}

void setcols_cb( Fl_Widget* w, void* v )
{
    Spreadsheet* table = (Spreadsheet*) v;
    Fl_Valuator* in = (Fl_Valuator*) w;
    int cols = int( in->value() ) + 1;
    table->cols( cols );
    table->redraw();
}

const double Spreadsheet::getVal( int r, int c )
{
    auto val = this->values[ r ][ c ];
    auto result = static_cast<double>( std::stoi( val ) );
    return result;
}

void Spreadsheet::event_callback( Fl_Widget*, void *v )
{
    ( (Spreadsheet*) v )->tableEvent();
}

void Spreadsheet::input_cb( Fl_Widget*, void* v )
{
    ( (Spreadsheet*) v )->set_value_hide();
}