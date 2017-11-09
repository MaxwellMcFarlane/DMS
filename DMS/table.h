#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <sqlite3.h>

using namespace std;


class Table
{
public:
    Table();
    Table(string tableName, sqlite3 * db);

//    string getTableName();
//    int getTableLength();
//    void addToTable(string cmd);
//    void delRow(string cmd);
//    void alterTable(string cmd);
//    void updateTable(string cmd);
//    string createQuery();

//    //callback methods
//    static int cbAddToTable (void *data, int argc, char **argv, char **azColName);
//    static int cbDelRow (void *data, int argc, char **argv, char **azColName);
//    static int cbAddToTable (void *data, int argc, char **argv, char **azColName);
//    static int cbDelRow (void *data, int argc, char **argv, char **azColName);

private:
    const char * tableName;
    int tableLength;
    string sensorTbDim = "(ID,TS,RAW DATA, CAL DATA, CALMODE)";
};

#endif // TABLE_H
