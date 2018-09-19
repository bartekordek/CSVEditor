#pragma once
#include <string>
#include <vector>
#include <memory>

class CSVFile
{
public:
    CSVFile();
    virtual ~CSVFile();

    void setDelimeter( const std::string& delimeter );
    void parseContents( const std::vector<std::string>& contents );
    const std::pair<bool, std::string> checkForCorrectness()const;
    const std::string& getVal( const unsigned int row, const unsigned int col )const;
    const unsigned int colCount()const;
    const unsigned int rowCount()const;
    const std::vector<std::vector<std::string>> getData()const;
    const std::vector<std::string>& getRowHeaders()const;
    const std::vector<std::string>& getColsHeaders()const;


protected:
private:
    std::vector<std::vector<std::string>> m_rows;
    std::vector<std::string> m_rowHeaders;
    std::string m_delimeter = ",";
};

