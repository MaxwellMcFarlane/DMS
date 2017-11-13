#include "dms.h"

DMS::DMS()
{

}

DMS::DMS(string name){
    int rc = 0;
    char *ermsg = 0;

    filename = name.c_str();
    rc = sqlite3_open(name.c_str(),&db);
    if(rc == SQLITE_OK){
        cerr << "DataBase " << filename << " is opened.";
    }
    else{
        cerr << "Error has occured.";
    }
}

//methods
void DMS::createTable(string name){
    Table * t = new Table(name,db);
    sensList.push_back(t);
}

Table* DMS::getTable(string tableName){
    for(int i = 0; i < (int)sensList.size(); i++){
        Table * t = sensList.at(i);
        if(tableName == t->getTableName()){return t;}
    }
}

void DMS::dumpTable(string tableName){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    string cmd = "DROP TABLE ";
    cmd += tableName;
    cmd += ";";
    cout << cmd << endl;

    sql = cmd.c_str();
    for(int i = 0; i < (int)sensList.size(); i++){
        Table * t = sensList.at(i);
        if(tableName == t->getTableName()){
            rc = sqlite3_exec(db,sql,cbDropTable,0,&ermsg);
            return;
        }
    }        

    if(rc != SQLITE_OK){
        cerr << "Row couldn't be deleted.\n";
    }
    else{
        cerr << "Row was deleted.\n";
    }
}

void DMS::renameTable(string tableName, string newName){}
void DMS::close(){
    sqlite3_close(db);
}

//Callback Functions
int DMS::cbDropTable(void *data, int argc, char **argv, char **azColName){
    if(argc < 1){
        cerr << "Table wasn't dropped.\n";
    }
    else{
        cerr << "Table was dropped.\n";
    }
    return 0;
}






