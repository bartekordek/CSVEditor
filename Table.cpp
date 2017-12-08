#include "Table.hpp"

RateTable::RateTable( int X, int Y, int W, int H, const char* L ):
    Fl_Scroll( X, Y, W, H, L )
{

}

void RateTable::setData( const std::vector<std::vector<std::string>>& vals )
{
    this->m_vals = vals;
    this->m_rowsCount = static_cast<int>( this->m_vals.size() );
    this->m_columnCount = static_cast<int>( this->m_vals.front().size() );
}

void RateTable::createCells()
{
    Fl_Tile *tile = new Fl_Tile( 
        m_columnCount, 
        m_rowsCount, 
        (int)(m_cellWidth*m_columnCount * 1.6), (int)(m_cellHeight*m_rowsCount * 1.2) );
    for (int r = 0; r<m_rowsCount; ++r)
    {
        std::vector<Fl_Widget*> columns;
        for (int c = 0; c<m_columnCount; ++c)
        {
            Pos pos = calcPosition( r, c );
            if (r == 0)
            {
                Fl_Box *box = new Fl_Box( 
                    pos.x, pos.y, 
                    m_cellWidth, m_cellHeight, 
                    this->m_vals.at( r ).at( c ).c_str() );
                box->box( FL_BORDER_BOX );
                columns.push_back( box );
            }
            else if (c == 0)
            {
                Fl_Input *in = new Fl_Input( pos.x, pos.y, m_cellWidth, m_cellHeight );
                in->box( FL_BORDER_BOX );
                in->value( this->m_vals.at( r ).at( c ).c_str() );
                columns.push_back( in );
            }
            else
            {
                Fl_Float_Input *in = new Fl_Float_Input( pos.x, pos.y, m_cellWidth, m_cellHeight );
                in->box( FL_BORDER_BOX );
                in->value( this->m_vals.at( r ).at( c ).c_str() );
                columns.push_back( in );
            }
            m_boxes.push_back( columns );
        }
    }
    tile->end();
    end();
}

const Pos RateTable::calcPosition( int row, int col )const
{
    Pos pos;
    pos.x = col * this->m_cellWidth + this->m_xOff;
    pos.y = row * this->m_cellHeight + this->m_yOff;
    return pos;
}