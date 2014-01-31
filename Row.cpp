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
#include <cassert>
#include <cstdio>

#include "Row.h"

template<typename T>
T GetValue( const std::string& str, const char* scanstr, T defaultValue )
{
    assert( scanstr );
    T temp;
    if( sscanf( str.c_str(), scanstr, &temp ) == 1 )
    {
        return temp;
    }
    else
    {
        return defaultValue;
    }
}

bool Row::ContainsRow( const std::string& rowname ) const
{
    return ( mRows.count(rowname) > 0 );
}

int Row::GetInt( const std::string& rowname ) const
{
    if( ContainsRow( rowname ) )
    {                
        return GetValue<int>( mRows.find(rowname)->second, "%d", (int)0 );
    }
    return 0;
}

unsigned int Row::GetUInt( const std::string& rowname ) const
{
    if( ContainsRow( rowname ) )
    {        
        return GetValue( mRows.find(rowname)->second, "%u", 0 );
    }
    return 0;
}

float Row::GetFloat( const std::string& rowname ) const
{
    if( ContainsRow( rowname ) )
    {        
        return GetValue( mRows.find(rowname)->second, "%f", 0.0f );
    }
    return 0.0f;
}

double Row::GetDouble( const std::string& rowname ) const
{     
    if( ContainsRow( rowname ) )
    {        
        return GetValue( mRows.find(rowname)->second, "%lf", 0.0 );
    }
    return 0.0;
}

std::string  Row::GetString( const std::string& rowname ) const
{
    if( ContainsRow( rowname ) )
    {
        return mRows.find(rowname)->second;
    }
    return "";
}

void Row::AddData( const char* col, const char* val )
{
    mRows[col] = val;
}