#include "CSVFile.h"

CSVFile::CSVFile()
{
}

CSVFile::~CSVFile()
{
}

void CSVFile::setDelimeter( const std::string& delimeter )
{
    this->m_delimeter = "\"" + delimeter + "\"";
}

void CSVFile::parseContents( const std::vector<std::string>& contents )
{
    for( const auto& line : contents )
    {
        std::vector<std::string> row;

        auto lineCp = line;
        auto delimeterPos = line.find( this->m_delimeter );
        unsigned colIndex = 0;
        while( delimeterPos != std::string::npos )
        {
            auto cell = lineCp.substr( 1, delimeterPos - 1 );
            row.push_back( cell );
            lineCp = lineCp.substr( delimeterPos + 2 );
            delimeterPos = lineCp.find( this->m_delimeter );

            if (0 == colIndex)
            {
                m_rowHeaders.push_back( cell );
            }
            ++colIndex;
        }

        this->m_rows.push_back( row );
    }
}

const std::pair<bool, std::string> CSVFile::checkForCorrectness()const
{
    std::pair<bool, std::string> result( true, "" );
    unsigned columnsCount = static_cast<unsigned>( ( this->m_rows.size() > 0 )?( this->m_rows[0].size() ): 0 );
    for( const auto& row: this->m_rows )
    {
        auto ccc = static_cast<unsigned>( row.size() );
        if( ccc != columnsCount )
        {
            result.first = false;
            result.second = "";
        }
    }
    return result;
}

const std::string& CSVFile::getVal( const unsigned int row, const unsigned int col )const
{
    return this->m_rows[row][col];
}

const unsigned int CSVFile::colCount()const
{
    const auto rowsCount = static_cast<unsigned int>( this->m_rows.size() );
    return rowsCount > 0 ? static_cast<unsigned int>( this->m_rows[0].size() ) : 0;
}

const unsigned int CSVFile::rowCount()const
{
    return static_cast<unsigned int>( this->m_rows.size() );
}

const std::vector<std::vector<std::string>> CSVFile::getData()const
{
    return this->m_rows;
}

const std::vector<std::string>& CSVFile::getRowHeaders()const
{
    return this->m_rowHeaders;
}

const std::vector<std::string>& CSVFile::getColsHeaders()const
{
    return this->m_rows.front();
}