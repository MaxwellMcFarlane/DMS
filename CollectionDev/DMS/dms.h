#ifndef DMS_H
#define DMS_H
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <vector>
#include "table.h"
#include "../../tools/macros.h"
#include "../../tools/baseclass.h"
#include "../../tools/log.h"
#include <time.h>
#include <cstring>

using namespace std;

class DMS
{
public:
    DMS();
    DMS(string name);
    DMS(string name, string dbConfig);
    DMS(string name, string dbConfig, string logPath);

    void createTable(string tableName);
    void createTable(string tableName, string dim);
    Table* getTable(string tableName);
    void dumpTable(string tableName);
    void close();
    Log* getLog();
    void getNewLog();
    void loadDataBase(string  myfile);
    vector<char*> delimitter(string cmd);
    bool controlQuery(string cmd);
    string getTableHeaders(string tableName);
    vector<Table*> getTableList();
    void loadConfigTable();
    bool isSensorExist(string sensorName);

private:

    //callback methods
    static int cbDropTable           (void *data, int argc, char **argv, char **azColName);
    static int cbgetTableHeaders     (void *data, int argc, char **argv, char **azColName);
    //used to manipulate table with correct info
    vector <Table*> sensList;
    string filename;
    Table lookup;
    sqlite3 *db;
    Log * log = new Log("log.txt");

};

#endif // DMS_H
