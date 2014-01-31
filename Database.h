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

#include "IDatabase.h"

class Database : public IDatabase
{
public:
    Database ();
    virtual ~Database (); 

    virtual bool OpenDatabase( const std::string& );
    virtual bool CloseDatabase( const std::string& );

    virtual Row Query( const char*, ... );
    virtual RowList MultiQuery( const char*, ... );

private:
    friend class DatabaseManager;

    static const int sMaxQueryLength = 1000000;

    class DatabaseData;

    DatabaseData *pDatabaseData;  

    static int s_callback(void *ptr, int argc, char **argv, char **azColName);
};