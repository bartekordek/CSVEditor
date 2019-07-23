#include "Spreadsheet.hpp"

NAMESPACE_BEGIN( SPRDSHTAPP )

Spreadsheet::Spreadsheet(
    int X, int Y,
    int W, int H,
    const char* L ):
    Fl_Table( X, Y, W, H, L )
{
    callback( &event_callback, ( void* ) this );
    when( static_cast<uchar>(FL_WHEN_NOT_CHANGED | when()) );
    // Create input widget that we'll use whenever user clicks on a cell
    input = new Fl_Int_Input( W / 2, H / 2, 0, 0 );
    input->hide();
    input->callback( input_cb, ( void* ) this );
    // callback triggered when user hits Enter
    input->when( FL_WHEN_ENTER_KEY_ALWAYS );
    input->maximum_size( 5 );
    input->color( FL_YELLOW );

    for( unsigned rowId = 0; rowId < MAX_ROWS; ++rowId )
    {
        Row row;
        for( unsigned colId = 0; colId < MAX_COLS; ++colId )
        {
            row.push_back( "0" );
        }
        this->m_values.push_back( row );
    }
    end();
    set_selection( 0, 0, 0, 0 );
}

Spreadsheet::~Spreadsheet()
{
}

void Spreadsheet::load( const Values& values )
{
    std::lock_guard<std::mutex> lock( this->valuesMtx );
    this->m_values = values;
}

void Spreadsheet::setValueHide()
{
    m_values[m_currentCellInfo.getRow()][m_currentCellInfo.getCol()] = input->value();
    input->hide();
    // XXX: if we don't do this, cursor can disappear!
    window()->cursor( FL_CURSOR_DEFAULT );
}

void Spreadsheet::startEditing( int R, int C )
{
    m_currentCellInfo.setBoth( static_cast<unsigned>( R ), static_cast<unsigned>( C ) );
    // Clear any previous multicell selection
    set_selection( R, C, R, C );
    int X, Y, W, H;
    
    find_cell( CONTEXT_CELL, R, C, X, Y, W, H ); // Find X/Y/W/H of cell
    // Move Fl_Input widget there
    input->resize( X, Y, W, H );
    input->value( m_values[R][C].c_str() );
    // Select entire input field
    input->position( 0, static_cast<int>( m_values[R][C].length() ) );
    // Show the input widget, now that we've positioned it
    input->show();
    input->take_focus();
}

void Spreadsheet::doneEditing()
{
    if( input->visible() )
    {
        // input widget visible, ie. edit in progress?
        setValueHide();
        // Transfer its current contents to cell and hide
    }
}

// Return the sum of all rows in this column
inline double Spreadsheet::sumRows( int C )
{
    double sum = 0.0;
    for( int r = 0; r < rows() - 1; ++r )			// -1: don't include cell data in 'totals' column
        sum += std::stod( m_values[r][C] );
    return( sum );
}

// Return the sum of all cols in this row

inline double Spreadsheet::sumCols( int R )
{
    double sum = 0.0;
    for( int c = 0; c < cols() - 1; ++c )			// -1: don't include cell data in 'totals' column
    {
        auto val = m_values[R][c];
        sum += std::stod( val );
    }
    return( sum );
}

// Return the sum of all cells in table

inline double Spreadsheet::sumAll()
{
    double sum = 0.0;
    for( int c = 0; c < cols() - 1; ++c )			// -1: don't include cell data in 'totals' column
    {
        for( int r = 0; r < rows() - 1; ++r )			// -1: ""
        {
            sum += std::stod( m_values[r][c] );
        }
    }
    return sum;
}

// Handle drawing all cells in table
void Spreadsheet::draw_cell(
    TableContext context,
    int R, int C,
    int X, int Y,
    int W, int H )
{
    TablePos cellInfo;
    cellInfo.setBoth( R, C );
    static std::string s;
    switch( context )
    {
    case CONTEXT_STARTPAGE:			// table about to redraw
    break;

    case CONTEXT_COL_HEADER:			// table wants us to draw a column heading (C is column)
    fl_font( FL_HELVETICA | FL_BOLD, 14 );	// set font for heading to bold
    fl_push_clip( X, Y, W, H );			// clip region for text
    {
        fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, col_header_color() );
        fl_color( FL_BLACK );
        if( C == cols() - 1 )
        {			// Last column? show 'TOTAL'
            fl_draw( "TOTAL", X, Y, W, H, FL_ALIGN_CENTER );
        }
        else
        {				// Not last column? show column letter
            s = 'A' + std::to_string( C );
            fl_draw( s.c_str(), X, Y, W, H, FL_ALIGN_CENTER );
        }
    }
    fl_pop_clip();
    return;

    case CONTEXT_ROW_HEADER:			// table wants us to draw a row heading (R is row)
        fl_font( FL_HELVETICA | FL_BOLD, 14 );	// set font for row heading to bold
        fl_push_clip( X, Y, W, H );
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, row_header_color() );
            fl_color( FL_BLACK );
            if( R == rows() - 1 )
            {			// Last row? Show 'Total'
                fl_draw( "TOTAL", X, Y, W, H, FL_ALIGN_CENTER );
            }
            else
            {				// Not last row? show row#
                s = std::to_string( R + 1 );
                fl_draw( s.c_str(), X, Y, W, H, FL_ALIGN_CENTER );
            }
        }
        fl_pop_clip();
    return;

    case CONTEXT_CELL:
    {			// table wants us to draw a cell
        if( cellInfo == m_currentCellInfo &&
            input->visible() )
        {
            return;					// dont draw for cell with input widget over it
        }
        // Background
        if( C < cols() - 1 && R < rows() - 1 )
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, is_selected( R, C ) ? FL_YELLOW : FL_WHITE );
        }
        else
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, is_selected( R, C ) ? 0xddffdd00 : 0xbbddbb00 );	// money green
        }
        // Text
        fl_push_clip( X + 3, Y + 3, W - 6, H - 6 );
        {
            fl_color( FL_BLACK );
            if( C == cols() - 1 || R == rows() - 1 )
            {	// Last row or col? Show total
                fl_font( FL_HELVETICA | FL_BOLD, 14 );	// ..in bold font
                if( C == cols() - 1 && R == rows() - 1 )
                {	// Last row+col? Total all cells
                    s = std::to_string( sumAll() );
                }
                else if( C == cols() - 1 )
                {		// Row subtotal
                    s = std::to_string( sumCols( R ) );
                }
                else if( R == rows() - 1 )
                {		// Col subtotal
                    s = std::to_string( sumRows( C ) );
                }
                fl_draw( s.c_str(), X + 3, Y + 3, W - 6, H - 6, FL_ALIGN_RIGHT );
            }
            else
            {				// Not last row or col? Show cell contents
                fl_font( FL_HELVETICA, 14 );		// ..in regular font
                fl_draw( m_values[R][C].c_str(), X + 3, Y + 3, W - 6, H - 6, FL_ALIGN_RIGHT );
            }
        }
        fl_pop_clip();
        return;
    }
    // table resizing rows or columns
    case CONTEXT_RC_RESIZE:
    if( input->visible() )
    {
        find_cell( CONTEXT_TABLE, m_currentCellInfo.getRow(), m_currentCellInfo.getCol(), X, Y, W, H );
        input->resize( X, Y, W, H );
        init_sizes();
    }
    return;

    default:
    return;
    }
}

// Callback whenever someone clicks on different parts of the table
void Spreadsheet::event_callback2()
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
            doneEditing();				// finish editing previous
            if( R != rows() - 1 && C != cols() - 1 )		// only edit cells not in total's columns
                startEditing( R, C );				// start new edit
            return;

        case FL_KEYBOARD:				// key press in table?
            if( Fl::event_key() == FL_Escape )
                exit( 0 );	// ESC closes app
            doneEditing();				// finish any previous editing
            if( C == cols() - 1 || R == rows() - 1 ) return;	// no editing of totals column
            switch( Fl::e_text[0] )
            {
            case '0': case '1': case '2': case '3':	// any of these should start editing new cell
            case '4': case '5': case '6': case '7':
            case '8': case '9': case '+': case '-':
                startEditing( R, C );			// start new edit
                input->handle( Fl::event() );		// pass typed char to input
            break;
            case '\r': case '\n':			// let enter key edit the cell
                startEditing( R, C );			// start new edit
            break;
            }
            return;
        }
        return;
    }

    case CONTEXT_TABLE:					// A table event occurred on dead zone in table
    case CONTEXT_ROW_HEADER:				// A table event occurred on row/column header
    case CONTEXT_COL_HEADER:
        doneEditing();					// done editing, hide
    return;

    default:
    return;
    }
}

// table's event callback (instance)

inline void Spreadsheet::event_callback( Fl_Widget *, void * v )
{	// table's event callback (static)
    ( ( Spreadsheet* ) v )->event_callback2();
}

inline void Spreadsheet::input_cb( Fl_Widget *, void * v )
{		// input widget's callback
    ( ( Spreadsheet* ) v )->setValueHide();
}

NAMESPACE_END( SPRDSHTAPP )