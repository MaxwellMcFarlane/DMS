#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <sqlite3.h>
#include <vector>

using namespace std;


class Table
{
public:
    Table();
    Table(string tableName, sqlite3 * db);

    string getTableName();
    int getTableLength();
    void addToTable(string info);
    void delRow(string col, string index);
    //provide cols, the table name, and operation
    string createQuery(string col, string op);
    void alterTable(string cmd);
    void updateTable(string cmd);    

    //callback methods
    static int cbAddToTable (void *data, int argc, char **argv, char **azColName);
    static int cbDelRow (void *data, int argc, char **argv, char **azColName);
    static int cbTableSize     (void *data, int argc, char **argv, char **azColName);
    static int cbCreateTable   (void *data, int argc, char **argv, char **azColName);
    static int cbCreateQuery   (void *data, int argc, char **argv, char **azColName);
private:
    string tableName;
    int tableLength;
    string lookupDim = "";
    string sensorTbDim = "(ID,TS,RAWDATA, CALDATA, CALMODE)";
    sqlite3 * db;
};

#endif // TABLE_H
