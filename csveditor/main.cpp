#pragma warning(push, 0)  

#include <stdio.h>
#include <string.h>
#include <string>

#include "Table.hpp"

static DemoTable *G_table = 0;

void setrows_cb( Fl_Widget*, void *data )
{
    auto in = (Fl_Input*)data;
    int rows = std::stoi( in->value() );
    if (rows < 0) rows = 0;
    G_table->rows( rows );
}

void setcols_cb( Fl_Widget*, void *data )
{
    auto in = (Fl_Input*)data;
    int cols = std::stoi( in->value() );
    if (cols < 0) cols = 0;
    G_table->cols( cols );
}

void setrowheader_cb( Fl_Widget*, void *data )
{
    Fl_Check_Button *check = (Fl_Check_Button*)data;
    G_table->row_header( check->value() );
}

void setcolheader_cb( Fl_Widget*, void *data )
{
    Fl_Check_Button *check = (Fl_Check_Button*)data;
    G_table->col_header( check->value() );
}

void setrowresize_cb( Fl_Widget*, void *data )
{
    Fl_Check_Button *check = (Fl_Check_Button*)data;
    G_table->row_resize( check->value() );
}

void setcolresize_cb( Fl_Widget*, void *data )
{
    Fl_Check_Button *check = (Fl_Check_Button*)data;
    G_table->col_resize( check->value() );
}

void setpositionrow_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int toprow = std::stoi( in->value() );
    if (toprow < 0 || toprow >= G_table->rows())
    {
        fl_alert( "Must be in range 0 thru #rows" );
    }
    else
    {
        G_table->row_position( toprow );
    }
}

void setpositioncol_cb( Fl_Widget *w, void *data )
{
    auto in = (Fl_Input*)data;
    int leftcol = std::stoi( in->value() );
    if (leftcol < 0 || leftcol >= G_table->cols())
    {
        fl_alert( "Must be in range 0 thru #cols" );
    }
    else
    {
        G_table->col_position( leftcol );
    }
}

void setrowheaderwidth_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 1) { val = 1; in->value( "1" ); }
    G_table->row_header_width( val );
}

void setcolheaderheight_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 1) { val = 1; in->value( "1" ); }
    G_table->col_header_height( val );
}

void setrowheadercolor_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { fl_alert( "Must be a color >0" ); }
    else { G_table->row_header_color( Fl_Color( val ) ); }
}

void setcolheadercolor_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { fl_alert( "Must be a color >0" ); }
    else { G_table->col_header_color( Fl_Color( val ) ); }
}

void setrowheightall_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { val = 0; in->value( "0" ); }
    G_table->row_height_all( val );
}

void setcolwidthall_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { val = 0; in->value( "0" ); }
    G_table->col_width_all( val );
}

void settablecolor_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { fl_alert( "Must be a color >0" ); }
    else { G_table->color( Fl_Color( val ) ); }
    G_table->redraw();
}

void setcellfgcolor_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { fl_alert( "Must be a color >0" ); }
    else { G_table->SetCellFGColor( Fl_Color( val ) ); }
    G_table->redraw();
}

void setcellbgcolor_cb( Fl_Widget *w, void *data )
{
    Fl_Input *in = (Fl_Input*)data;
    int val = std::stoi( in->value() );
    if (val < 0) { fl_alert( "Must be a color >0" ); }
    else { G_table->SetCellBGColor( Fl_Color( val ) ); }
    G_table->redraw();
}

char *itoa( int val )
{
    static char s[80];
    sprintf( s, "%d", val );
    return(s);
}

void tablebox_choice_cb( Fl_Widget *w, void *data )
{
    G_table->table_box( (Fl_Boxtype)(fl_intptr_t)data );
    G_table->redraw();
}

void widgetbox_choice_cb( Fl_Widget *w, void *data )
{
    G_table->box( (Fl_Boxtype)(fl_intptr_t)data );
    G_table->resize( G_table->x(), G_table->y(), G_table->w(), G_table->h() );
}

void type_choice_cb( Fl_Widget *w, void *data )
{
    G_table->type( (Fl_Table_Row::TableRowSelectMode)(fl_intptr_t)data );
}

Fl_Menu_Item tablebox_choices[] = {
    { "No Box",         0, tablebox_choice_cb, (void*)FL_NO_BOX },
    { "Flat Box",       0, tablebox_choice_cb, (void*)FL_FLAT_BOX },
    { "Up Box",         0, tablebox_choice_cb, (void*)FL_UP_BOX },
    { "Down Box",       0, tablebox_choice_cb, (void*)FL_DOWN_BOX },
    { "Up Frame",       0, tablebox_choice_cb, (void*)FL_UP_FRAME },
    { "Down Frame",     0, tablebox_choice_cb, (void*)FL_DOWN_FRAME },
    { "Thin Up Box",    0, tablebox_choice_cb, (void*)FL_THIN_UP_BOX },
    { "Thin Down Box",  0, tablebox_choice_cb, (void*)FL_THIN_DOWN_BOX },
    { "Thin Up Frame",  0, tablebox_choice_cb, (void*)FL_THIN_UP_FRAME },
    { "Thin Down Frame",0, tablebox_choice_cb, (void*)FL_THIN_DOWN_FRAME },
    { "Engraved Box",   0, tablebox_choice_cb, (void*)FL_ENGRAVED_BOX },
    { "Embossed Box",   0, tablebox_choice_cb, (void*)FL_EMBOSSED_BOX },
    { "Engraved Frame", 0, tablebox_choice_cb, (void*)FL_ENGRAVED_FRAME },
    { "Embossed Frame", 0, tablebox_choice_cb, (void*)FL_EMBOSSED_FRAME },
    { "Border Box",     0, tablebox_choice_cb, (void*)FL_BORDER_BOX },
    { "Shadow Box",     0, tablebox_choice_cb, (void*)FL_SHADOW_BOX },
    { "Border Frame",   0, tablebox_choice_cb, (void*)FL_BORDER_FRAME },
    { 0 }
};

Fl_Menu_Item widgetbox_choices[] = {
    { "No Box",         0, widgetbox_choice_cb, (void*)FL_NO_BOX },
    //{"Flat Box",       0, widgetbox_choice_cb, (void*)FL_FLAT_BOX },
    //{"Up Box",         0, widgetbox_choice_cb, (void*)FL_UP_BOX },
    //{"Down Box",       0, widgetbox_choice_cb, (void*)FL_DOWN_BOX },
    { "Up Frame",       0, widgetbox_choice_cb, (void*)FL_UP_FRAME },
    { "Down Frame",     0, widgetbox_choice_cb, (void*)FL_DOWN_FRAME },
    //{"Thin Up Box",    0, widgetbox_choice_cb, (void*)FL_THIN_UP_BOX },
    //{"Thin Down Box",  0, widgetbox_choice_cb, (void*)FL_THIN_DOWN_BOX },
    { "Thin Up Frame",  0, widgetbox_choice_cb, (void*)FL_THIN_UP_FRAME },
    { "Thin Down Frame",0, widgetbox_choice_cb, (void*)FL_THIN_DOWN_FRAME },
    //{"Engraved Box",   0, widgetbox_choice_cb, (void*)FL_ENGRAVED_BOX },
    //{"Embossed Box",   0, widgetbox_choice_cb, (void*)FL_EMBOSSED_BOX },
    { "Engraved Frame", 0, widgetbox_choice_cb, (void*)FL_ENGRAVED_FRAME },
    { "Embossed Frame", 0, widgetbox_choice_cb, (void*)FL_EMBOSSED_FRAME },
    //{"Border Box",     0, widgetbox_choice_cb, (void*)FL_BORDER_BOX },
    //{"Shadow Box",     0, widgetbox_choice_cb, (void*)FL_SHADOW_BOX },
    { "Border Frame",   0, widgetbox_choice_cb, (void*)FL_BORDER_FRAME },
    { 0 }
};

Fl_Menu_Item type_choices[] = {
    { "SelectNone",         0, type_choice_cb, (void*)Fl_Table_Row::SELECT_NONE },
    { "SelectSingle",       0, type_choice_cb, (void*)Fl_Table_Row::SELECT_SINGLE },
    { "SelectMulti",        0, type_choice_cb, (void*)Fl_Table_Row::SELECT_MULTI },
    { 0 }
};

int main( int argc, char **argv )
{
    Fl_Window win( 900, 730 );

    G_table = new DemoTable( 20, 20, 860, 460, "Demo" );
    G_table->selection_color( FL_YELLOW );
    G_table->when( FL_WHEN_RELEASE | FL_WHEN_CHANGED );
    G_table->table_box( FL_NO_BOX );
    G_table->col_resize_min( 4 );
    G_table->row_resize_min( 4 );

    // ROWS
    G_table->row_header( 1 );
    G_table->row_header_width( 60 );
    G_table->row_resize( 1 );
    G_table->rows( 500 );
    G_table->row_height_all( 20 );

    // COLS
    G_table->cols( 500 );
    G_table->col_header( 1 );
    G_table->col_header_height( 25 );
    G_table->col_resize( 1 );
    G_table->col_width_all( 80 );

    // Add children to window
    win.begin();

    // ROW
    Fl_Input setrows( 150, 500, 120, 25, "Rows" );
    setrows.labelsize( 12 );
    setrows.value( itoa( G_table->rows() ) );
    setrows.callback( setrows_cb, (void*)&setrows );
    setrows.when( FL_WHEN_RELEASE );

    Fl_Input rowheightall( 400, 500, 120, 25, "Row Height" );
    rowheightall.labelsize( 12 );
    rowheightall.value( itoa( G_table->row_height( 0 ) ) );
    rowheightall.callback( setrowheightall_cb, (void*)&rowheightall );
    rowheightall.when( FL_WHEN_RELEASE );

    Fl_Input positionrow( 650, 500, 120, 25, "Row Position" );
    positionrow.labelsize( 12 );
    positionrow.value( "1" );
    positionrow.callback( setpositionrow_cb, (void*)&positionrow );
    positionrow.when( FL_WHEN_RELEASE );

    // COL
    Fl_Input setcols( 150, 530, 120, 25, "Cols" );
    setcols.labelsize( 12 );
    setcols.value( itoa( G_table->cols() ) );
    setcols.callback( setcols_cb, (void*)&setcols );
    setcols.when( FL_WHEN_RELEASE );

    Fl_Input colwidthall( 400, 530, 120, 25, "Col Width" );
    colwidthall.labelsize( 12 );
    colwidthall.value( itoa( G_table->col_width( 0 ) ) );
    colwidthall.callback( setcolwidthall_cb, (void*)&colwidthall );
    colwidthall.when( FL_WHEN_RELEASE );

    Fl_Input positioncol( 650, 530, 120, 25, "Col Position" );
    positioncol.labelsize( 12 );
    positioncol.value( "1" );
    positioncol.callback( setpositioncol_cb, (void*)&positioncol );
    positioncol.when( FL_WHEN_RELEASE );

    // ROW HEADER
    Fl_Input rowheaderwidth( 150, 570, 120, 25, "Row Header Width" );
    rowheaderwidth.labelsize( 12 );
    rowheaderwidth.value( itoa( G_table->row_header_width() ) );
    rowheaderwidth.callback( setrowheaderwidth_cb, (void*)&rowheaderwidth );
    rowheaderwidth.when( FL_WHEN_RELEASE );

    Fl_Input rowheadercolor( 400, 570, 120, 25, "Row Header Color" );
    rowheadercolor.labelsize( 12 );
    rowheadercolor.value( itoa( (int)G_table->row_header_color() ) );
    rowheadercolor.callback( setrowheadercolor_cb, (void*)&rowheadercolor );
    rowheadercolor.when( FL_WHEN_RELEASE );

    Fl_Check_Button rowheader( 550, 570, 120, 25, "Row Headers?" );
    rowheader.labelsize( 12 );
    rowheader.callback( setrowheader_cb, (void*)&rowheader );
    rowheader.value( G_table->row_header() ? 1 : 0 );

    Fl_Check_Button rowresize( 700, 570, 120, 25, "Row Resize?" );
    rowresize.labelsize( 12 );
    rowresize.callback( setrowresize_cb, (void*)&rowresize );
    rowresize.value( G_table->row_resize() ? 1 : 0 );

    // COL HEADER
    Fl_Input colheaderheight( 150, 600, 120, 25, "Col Header Height" );
    colheaderheight.labelsize( 12 );
    colheaderheight.value( itoa( G_table->col_header_height() ) );
    colheaderheight.callback( setcolheaderheight_cb, (void*)&colheaderheight );
    colheaderheight.when( FL_WHEN_RELEASE );

    Fl_Input colheadercolor( 400, 600, 120, 25, "Col Header Color" );
    colheadercolor.labelsize( 12 );
    colheadercolor.value( itoa( (int)G_table->col_header_color() ) );
    colheadercolor.callback( setcolheadercolor_cb, (void*)&colheadercolor );
    colheadercolor.when( FL_WHEN_RELEASE );

    Fl_Check_Button colheader( 550, 600, 120, 25, "Col Headers?" );
    colheader.labelsize( 12 );
    colheader.callback( setcolheader_cb, (void*)&colheader );
    colheader.value( G_table->col_header() ? 1 : 0 );

    Fl_Check_Button colresize( 700, 600, 120, 25, "Col Resize?" );
    colresize.labelsize( 12 );
    colresize.callback( setcolresize_cb, (void*)&colresize );
    colresize.value( G_table->col_resize() ? 1 : 0 );

    Fl_Choice tablebox( 150, 640, 120, 25, "Table Box" );
    tablebox.labelsize( 12 );
    tablebox.textsize( 12 );
    tablebox.menu( tablebox_choices );
    tablebox.value( 0 );

    Fl_Choice widgetbox( 150, 670, 120, 25, "Widget Box" );
    widgetbox.labelsize( 12 );
    widgetbox.textsize( 12 );
    widgetbox.menu( widgetbox_choices );
    widgetbox.value( 2 );		// down frame

    Fl_Input tablecolor( 400, 640, 120, 25, "Table Color" );
    tablecolor.labelsize( 12 );
    tablecolor.value( itoa( (int)G_table->color() ) );
    tablecolor.callback( settablecolor_cb, (void*)&tablecolor );
    tablecolor.when( FL_WHEN_RELEASE );

    Fl_Input cellbgcolor( 400, 670, 120, 25, "Cell BG Color" );
    cellbgcolor.labelsize( 12 );
    cellbgcolor.value( itoa( (int)G_table->GetCellBGColor() ) );
    cellbgcolor.callback( setcellbgcolor_cb, (void*)&cellbgcolor );
    cellbgcolor.when( FL_WHEN_RELEASE );

    Fl_Input cellfgcolor( 400, 700, 120, 25, "Cell FG Color" );
    cellfgcolor.labelsize( 12 );
    cellfgcolor.value( itoa( (int)G_table->GetCellFGColor() ) );
    cellfgcolor.callback( setcellfgcolor_cb, (void*)&cellfgcolor );
    cellfgcolor.when( FL_WHEN_RELEASE );

    Fl_Choice type( 650, 640, 120, 25, "Type" );
    type.labelsize( 12 );
    type.textsize( 12 );
    type.menu( type_choices );
    type.value( 2 );

    win.end();
    win.resizable( *G_table );
    win.show( argc, argv );

    return(Fl::run());
}
#pragma warning(pop)