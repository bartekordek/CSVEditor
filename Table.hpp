#pragma once
#pragma warning(push, 0)  
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#pragma warning(pop)

#include <vector>
#define NDEBUG
#define COLS 9
#define ROWS 20

struct Pos
{
    int x = 0;
    int y = 0;
};

class RateTable : public Fl_Scroll
{
public:
    RateTable( int X, int Y, int W, int H, const char*L = 0 );
    void setData( const std::vector<std::vector<std::string>>& vals );
    void createCells();
protected:
private:
    
    const Pos calcPosition( int row, int col )const;

    std::vector<std::vector<Fl_Widget*>> m_boxes;
    std::vector<std::vector<std::string>> m_vals;
    int m_cellWidth = 80;
    int m_cellHeight = 30;
    int m_columnCount = 0;
    int m_rowsCount = 0;
    int m_xOff = 50;
    int m_yOff = 50;
};
