#ifndef DMS_H
#define DMS_H
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "table.h"

using namespace std;

class DMS
{
public:
    DMS();
    DMS(string name);    

    //method@1: create table
    void createTable(string tableName);
    //method@2: get table (directly through db)
    Table* getTable(string tableName);       
    //method@3: dump table
    void dumpTable(string tableName);
    //method@4: rename table
    void renameTable(string tableName, string newName);
    //method@5: close database
    void close();
    //method@6: close database
    void checkExist(string tableName);

private:

    //callback methods
    static int cbDropTable     (void *data, int argc, char **argv, char **azColName);
    static int cbListAllTables(void *data, int argc, char **argv, char **azColName);
    static int cbCheckExist(void *data, int argc, char **argv, char **azColName);
    //used to manipulate table with correct info
    vector <Table*> sensList;
    string filename;
    Table lookup;
    sqlite3 *db;
};

#endif // DMS_H
