#include "dms.h"

DMS::DMS()
{
    time_t now = time(0);
    string dt = ctime(&now);

    *log << "\n" << dt;
    *log << "Error: No database given\n";
}

DMS::DMS(string name, string dbConfig){
    int rc = 0;
    char *ermsg = 0;
    time_t now = time(0);
    string dt = ctime(&now);

    *log << "\n" << dt;

    filename = name.c_str();
    rc = sqlite3_open(name.c_str(),&db);
    if(rc == SQLITE_OK){
        *log << "DataBase " << filename << " is opened.\n";
    }
    else{
        *log <<"Error: " << rc << " has occured.\n";
    }

    string tableName,dimensions;
    ifstream myconfig(dbConfig);

    if(myconfig.is_open()){
        while(!myconfig.eof()){
            getline(myconfig,tableName);
            getline(myconfig,dimensions);
            createTable(tableName,dimensions);
            getline(myconfig,dimensions);
            cout << dimensions;
            getTable(tableName)->setDimensions(dimensions);
        }
        myconfig.close();
    }
    else{*log << "Unable to open file.\n"; cerr << "Unable to open file.\n";}

}

DMS::DMS(string name){
    int rc = 0;
    char *ermsg = 0;
    //current time
    time_t now = time(0);
    string dt = ctime(&now);

    *log << "\n" << dt;

    filename = name.c_str();
    rc = sqlite3_open(name.c_str(),&db);
    if(rc == SQLITE_OK){
        *log << "DataBase " << filename << " is opened.\n";
    }
    else{
        *log <<"Error: " << rc << " has occured.\n";
    }
}

//methods
void DMS::createTable(string name){
    Table * t = new Table(name,db,log);
    sensList.push_back(t);    
}

void DMS::createTable(string name, string dim){
    Table * t = new Table(name,dim, db,log);
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
//    cout << cmd << endl;
    Table * t;
    sql = cmd.c_str();
    for(int i = 0; i < (int)sensList.size(); i++){
        t = sensList.at(i);
        if(tableName == t->getTableName()){
            rc = sqlite3_exec(db,sql,cbDropTable,(void*)log,&ermsg);
            break;
        }
    }        

    if(rc != SQLITE_OK){
        *log << "Error: " << rc << " Table: " << t->getTableName() << " wasn't be deleted.\n";
    }
    else{
        *log << "Table: " << t->getTableName() << " was deleted.\n";
    }
}

void DMS::checkExist(string tableName){}
void DMS::renameTable(string tableName, string newName){}

Log* DMS::getLog(){return log;}

void DMS::close(){
    sqlite3_close(db);
    //current time
    time_t now = time(0);
    string dt = ctime(&now);

    *log << dt;
}

//Callback Functions
int DMS::cbDropTable(void *data, int argc, char **argv, char **azColName){
    Log * log0 = (Log *) data;
    int i;
    for(i = 0; i < argc; i++){*log0 << azColName[i] << " ";}
    *log0 << "\n";
    return 0;
}






