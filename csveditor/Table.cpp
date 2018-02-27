#include "Table.hpp"

#pragma warning(push, 0)

void DemoTable::draw_cell( TableContext context,
    int R, int C, int X, int Y, int W, int H )
{
    static char s[40];
    sprintf( s, "%d/%d", R, C );		// text for each cell

    switch (context)
    {
    case CONTEXT_STARTPAGE:
        fl_font( FL_HELVETICA, 16 );
        return;

    case CONTEXT_COL_HEADER:
        fl_push_clip( X, Y, W, H );
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, col_header_color() );
            fl_color( FL_BLACK );
            fl_draw( s, X, Y, W, H, FL_ALIGN_CENTER );
        }
        fl_pop_clip();
        return;

    case CONTEXT_ROW_HEADER:
        fl_push_clip( X, Y, W, H );
        {
            fl_draw_box( FL_THIN_UP_BOX, X, Y, W, H, row_header_color() );
            fl_color( FL_BLACK );
            fl_draw( s, X, Y, W, H, FL_ALIGN_CENTER );
        }
        fl_pop_clip();
        return;

    case CONTEXT_CELL:
    {
        fl_push_clip( X, Y, W, H );
        {
            // BG COLOR
            fl_color( row_selected( R ) ? selection_color() : cell_bgcolor );
            fl_rectf( X, Y, W, H );

            // TEXT
            fl_color( cell_fgcolor );
            fl_draw( s, X, Y, W, H, FL_ALIGN_CENTER );

            // BORDER
            fl_color( color() );
            fl_rect( X, Y, W, H );
        }
        fl_pop_clip();
        return;
    }

    case CONTEXT_TABLE:
        fprintf( stderr, "TABLE CONTEXT CALLED\n" );
        return;

    case CONTEXT_ENDPAGE:
    case CONTEXT_RC_RESIZE:
    case CONTEXT_NONE:
        return;
    }
}

// Callback whenever someone clicks on different parts of the table
void DemoTable::event_callback( Fl_Widget*, void *data )
{
    DemoTable *o = (DemoTable*)data;
    o->event_callback2();
}

void DemoTable::event_callback2()
{
    int R = callback_row(),
        C = callback_col();
    TableContext context = callback_context();
    printf( "'%s' callback: ", (label() ? label() : "?") );
    printf( "Row=%d Col=%d Context=%d Event=%d InteractiveResize? %d\n",
        R, C, (int)context, (int)Fl::event(), (int)is_interactive_resize() );
}

#pragma warning(pop)