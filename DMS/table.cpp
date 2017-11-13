#include "table.h"

Table::Table()
{

}

Table::Table(string tableName, sqlite3 *db){

    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    this->tableName = tableName.c_str();
    this->db = db;

    string cmd;

    if(tableName == "LOOKUP"){
          cmd = "CREATE TABLE ";
            cmd += tableName;
            cmd +=
            "(ID BLOB PRIMARY KEY  NOT NULL);";
    }
    else if(tableName.at(0) == 'S'){
        cmd = "CREATE TABLE ";
        cmd += tableName;
        cmd += " (ID INT PRIMARY KEY NOT NULL, "
                     "TS BLOB NOT NULL, "
                       "RAWDATA BLOB NOT NULL, "
                       "CALDATA BLOB NOT NULL, "
                       "CALMODE INT NOT NULL);";
    }
    sql = cmd.c_str();
    cout << sql << endl;
    rc = sqlite3_exec(db,sql,cbCreateTable,0, &ermsg);

    if(rc != SQLITE_OK){
        cerr << tableName << " could not be created.\n";
    }
    else{
        cerr << tableName << " was created.\n";
    }
    tableLength = 0;
}

string Table::getTableName(){return tableName;}
int Table::getTableLength(){return tableLength;}

//table methods
void Table::addToTable(string info){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    string cmd = "INSERT INTO ";
    cmd+= tableName;
    if(tableName == "LOOKUP"){cmd += lookupDim;}
    else if(tableName.at(0) == 'S'){cmd += sensorTbDim;}
    cmd+=" VALUES(";
    cmd += info;
    cmd += ");";
    cout << cmd << endl;

    sql = cmd.c_str();

    rc = sqlite3_exec(db,sql,cbAddToTable,0, &ermsg);

    if(rc != SQLITE_OK){
        cerr << "Item could not be inserted.\n";
    }
    else{
        cerr << "Item was inserted.\n";
        tableLength++;
    }
}



void Table::delRow(string col, string index){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    string cmd = "DELETE FROM ";
    cmd += tableName;
    cmd += " WHERE ";
    cmd += col;
    cmd += " = ";
    cmd += index;
    cmd += ";";
    cout << cmd << endl;

    sql = cmd.c_str();

    rc = sqlite3_exec(db,sql,cbDelRow,0, &ermsg);

    if(rc != SQLITE_OK){
        cerr << "Row couldn't be deleted.\n";
    }
    else{
        cerr << "Row was deleted.\n";
        tableLength--;
    }
}

string Table::createQuery(string col, string op){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;

    string cmd = "SELECT ";
    cmd += col;
    cmd += " FROM ";
    cmd += tableName;
    if(!op.empty()){
        cmd += " WHERE ";
        cmd += op;
    }
    cmd += ";";
    cout << cmd << endl;
    sql = cmd.c_str();

    string result;
    rc = sqlite3_exec(db,sql,cbCreateQuery,&result, &ermsg);

    cout << result << endl;

    if(rc == SQLITE_ERROR){
        cerr << "Query wasn't created.\n";
    }
    else{
        cerr << "Queary created.\n";
    }

    return result;
}

//callback methods

int Table::cbCreateTable(void *data, int argc, char **argv, char **azColName){
    if(argc < 1){
        cerr << "Table couldn't be created\n";
    }
    else{
        cerr << "Table could be created.\n";
    }
    return 0;
}

int Table::cbAddToTable(void *data, int argc, char **argv, char **azColName){
    if(argc < 1){
        cerr << "Couldn't add to table.\n";
    }
    else{
        cerr << "Data has been added to table.\n";
    }
    return 0;
}

int Table::cbDelRow(void *data, int argc, char **argv, char **azColName){
    if(argc < 1){
        cerr << "Row couldn't be deleted.\n";
    }
    else{
        cerr << "Row was deleted.\n";
    }
    return 0;
}

int Table::cbCreateQuery(void *data, int argc, char **argv, char **azColName){
    int i;
    string * result = (string *) data;
    for(i = 0; i < argc; i++){*result += argv[i];if(i < argc-1){*result += "|";}}
    *result += "\n";
    return 0;
}

