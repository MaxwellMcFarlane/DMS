#ifndef DMS_H
#define DMS_H
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <vector>
#include "table.h"
#include "../tools/macros.h"
#include "../tools/config.h"
#include "../tools/baseclass.h"
#include "../tools/log.h"

using namespace std;

class DMS
{
public:
    DMS();
    DMS(string name);    
    DMS(string name, string dbConfig);

    //method@1: create table
    void createTable(string tableName);
    void createTable(string tableName, string dim);
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
    Log* getLog();
    void dumpLog();

private:

    //callback methods
    static int cbDropTable     (void *data, int argc, char **argv, char **azColName);
    static int cbCheckExist(void *data, int argc, char **argv, char **azColName);
    //used to manipulate table with correct info
    vector <Table*> sensList;
    string filename;
    Table lookup;
    sqlite3 *db;
    Log * log = new Log("log.txt");

};

#endif // DMS_H
