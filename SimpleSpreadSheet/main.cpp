//
// "$Id: pack.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Fl_Pack test program for the Fast Light Tool Kit (FLTK).
//
// Rather crude test of the Fl_Pack object.
// Changing the type() of an Fl_Pack after it is displayed is not supported
// so I have to do a lot of resizing of things before that.
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Pack.H>
#include <math.h>

#include <string>
#include <vector>

Fl_Pack *pack;
Fl_Scroll *scroll;

void type_cb( Fl_Light_Button*, long widgetType )
{
    for( int i = 0; i < pack->children(); i++ )
    {
        Fl_Widget* o = pack->child( i );
        o->resize( 0, 0, 25, 25 );
    }
    pack->resize( scroll->x(), scroll->y(), scroll->w(), scroll->h() );
    pack->parent()->redraw();
    pack->type( uchar( widgetType ) );
    pack->redraw();
}

void spacing_cb( Fl_Value_Slider*o, long ) {
    pack->spacing( int( o->value() ) );
    scroll->redraw();
}

class Button: public Fl_Button
{
public:
    Button( int x, int y, int w, int h ):
        Fl_Button( x, y, w, h )
    {

    }

    void setLabel( const std::string& label )
    {
        m_label = label;
        Fl_Button::label( m_label.c_str() );
    }

protected:
private:
    std::string m_label;

};

int main( int argc, char **argv )
{
    std::vector<Button> buttons;

    auto w = new Fl_Double_Window( 360, 370 );
    scroll = new Fl_Scroll( 10, 10, 340, 285 );
    {
        auto o = new Fl_Pack( 10, 10, 340, 285 );
        pack = o;
        o->box( FL_DOWN_FRAME );
        //o->box(FL_ENGRAVED_FRAME);

        new Fl_Button( 25, 25, 25, 25, "CHUJ" );

        for( size_t i = 1; i < 25; ++i )
        {
            int val = 35 + 10 * ( i - 1 );
            std::string valueAsString = "DUPA: " + std::to_string( i );
            auto button = new Button( val, val, 25, 25 );
            button->setLabel( valueAsString );
        }
        o->end();
        w->resizable( o );
    }
    scroll->end();
    {
        Fl_Light_Button* o = new Fl_Light_Button( 10, 305, 165, 25, "HORIZONTAL" );
        o->type( FL_RADIO_BUTTON );
        o->callback( ( Fl_Callback* ) type_cb, ( void* ) ( Fl_Pack::HORIZONTAL ) );
    }
    {
        Fl_Light_Button* o = new Fl_Light_Button( 185, 305, 165, 25, "VERTICAL" );
        o->type( FL_RADIO_BUTTON );
        o->value( 1 );
        o->callback( ( Fl_Callback* ) type_cb, ( void* ) ( Fl_Pack::VERTICAL ) );
    }
    {
        Fl_Value_Slider* o = new Fl_Value_Slider( 100, 335, 250, 25, "Spacing: " );
        o->align( FL_ALIGN_LEFT );
        o->type( FL_HORIZONTAL );
        o->range( 0, 30 );
        o->step( 1 );
        o->callback( ( Fl_Callback* ) spacing_cb );
    }
    w->end();

    w->show( argc, argv );
    Fl::run();
    return  0;
}