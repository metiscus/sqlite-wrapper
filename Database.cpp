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
#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <cstdarg>
#include "Database.h"
#include <functional>
//#include "Logging.h"
#include "sqlite3.h"

class Database::DatabaseData
{
public:
    DatabaseData ( )
    {
        pDb = NULL;
    }

    ~DatabaseData( )
    {
        assert(pDb == NULL);       
    }

    sqlite3 *pDb;

};

Database::Database ()
{
    pDatabaseData = new DatabaseData( );
}

Database::~Database ()
{
    if( pDatabaseData != NULL )
    {
        delete pDatabaseData;
        pDatabaseData = NULL;
    }
}

int Database::s_callback(void *ptr, int argc, char **argv, char **azColName)
{
    assert(ptr);
    RowList *pRowList = (RowList*)ptr;
    Row row;
    for( int ii=0; ii<argc; ++ii )
    {        
        row.AddData( azColName[ii], argv[ii] );
    }
    pRowList->push_back( row );
    return 0;
}

Row Database::Query( const char* format, ... )
{
    assert(pDatabaseData && pDatabaseData->pDb);

    va_list args;

    char *buffer = new char[sMaxQueryLength];
    va_start(args, format);
    vsnprintf(buffer, sMaxQueryLength, format, args);
    va_end(args);

    RowList result;

    sqlite3_stmt *pStatement = NULL;
    char *errMsg = 0;
    int rc = sqlite3_exec(pDatabaseData->pDb, buffer, s_callback, &result, &errMsg);
    /* Execute SQL statement */
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s, query:'%s'\n", errMsg, buffer);
        sqlite3_free(errMsg);
    }

    delete[] buffer;

    if( result.size() > 0 )
    {
        return result[0];
    }
    else
    {
        return Row();
    }
}

RowList Database::MultiQuery( const char* format, ... )
{
    assert(pDatabaseData && pDatabaseData->pDb);

    va_list args;

    char *buffer = new char[sMaxQueryLength];
    va_start(args, format);
    vsnprintf(buffer, sMaxQueryLength, format, args);
    va_end(args);

    RowList result;

    sqlite3_stmt *pStatement = NULL;
    char *errMsg = 0;
    int rc = sqlite3_exec(pDatabaseData->pDb, buffer, s_callback, &result, &errMsg);
    /* Execute SQL statement */
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else
    {
        fprintf(stdout, "Table created successfully\n");
    }

    delete[] buffer;

    return result;
}

bool Database::OpenDatabase( const std::string& filename )
{
    assert(pDatabaseData && !pDatabaseData->pDb);
    return ( SQLITE_OK == sqlite3_open(filename.c_str(), &pDatabaseData->pDb) );
}

bool Database::CloseDatabase( const std::string& )
{
    assert(pDatabaseData && pDatabaseData->pDb);
    if( nullptr != pDatabaseData )
    {
        sqlite3_close( pDatabaseData->pDb );
    }
    return false;
}