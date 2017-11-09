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

    //method@1: create table
    void createTable(string cmd);
    //method@2: get table (directly through db)
    void getTable(string cmd);
    //method@3: get query
    void getQuery(string cmd);
    //method@4: dump table
    void dumpTable(string cmd);
    //method@5: rename table
    void renameTable(string name);
    //method@6: close database
    void close();

private:

    //callback methods
    static int cb_drop_table     (void *data, int argc, char **argv, char **azColName);
    static int cb_table_size     (void *data, int argc, char **argv, char **azColName);
    static int cb_list_all_tables(void *data, int argc, char **argv, char **azColName);
    static int cb_check_existance(void *data, int argc, char **argv, char **azColName);
    static int cbCreateTable   (void *data, int argc, char **argv, char **azColName);
    //used to manipulate table with correct info
//    vector <*Table> sensList;
    Table lookup;
    sqlite3 *db;
};

#endif // DMS_H
