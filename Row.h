/*
        This file is part of UnknownDevices

    UnknownDevices is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    UnknownDevices is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with UnknownDevices.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <map>
#include <string>
#include <vector>

class Row
{
public:
    int          GetInt( const std::string& ) const;
    unsigned int GetUInt( const std::string& ) const;
    float        GetFloat( const std::string& ) const;
    double       GetDouble( const std::string& ) const;
    std::string  GetString( const std::string& ) const;

    void AddData( const char* col, const char* val );

private:
    typedef std::map<std::string, std::string> StringMap;

    StringMap mRows;

    bool ContainsRow( const std::string& ) const;
};

typedef std::vector<Row> RowList;