#include "table.h"

Table::Table()
{

}

Table::Table(string tableName, string dim, sqlite3 *db, Log *log){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    this->tableName = tableName;
    this->dimensions = dim;

    this->db = db;
    string cmd;
    this->log = log;
    cmd += "CREATE TABLE ";
    cmd += tableName + " " + dim;
    sql = cmd.c_str();

    rc = sqlite3_exec(db,sql,cbCreateTable,0, &ermsg);

    if(rc != SQLITE_OK){
        *log << "Error: " << rc << "\n";
        if(rc == 1){*log << "Table:" << tableName << " already exists.\n";}
        *log << tableName << " could not be created.\n";
    }
    else{
        *log << tableName << " was created.\n";
        *log << "Dimensions: " << dim << "\n";
    }
    tableLength = 0;
}

Table::Table(string tableName, sqlite3 *db, Log * log){

    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    this->tableName = tableName.c_str();
    this->db = db;

    this->log = log;
    string cmd;

    if(tableName == "HubTable"){
          cmd = "CREATE TABLE ";
            cmd += tableName;
            cmd +=
            "(HubSN TEXT PRIMARY KEY  NOT NULL,"
            "NumberOfSensors TEXT NOT NULL);";
    }
    else if(tableName == "SampleTable"){
        cmd = "CREATE TABLE ";
        cmd += tableName;
        cmd += " (Sample TEXT PRIMARY KEY NOT NULL, "
                     "SensorID TEXT NOT NULL, "
                       "RawData TEXT NOT NULL, "
                       "CalData TEXT);";
    }
    else if(tableName == "CalibrationTable"){
        cmd = "CREATE TABLE ";
        cmd += tableName;
        cmd += " (CalIndex INT PRIMARY KEY NOT NULL, "
                     "Sample BLOB NOT NULL, "
                       "ModelNumber BLOB NOT NULL, "
                       "CalibrationTimeStamp BLOB NOT NULL, "
                       "CalibrationValue BLOB NOT NULL);";
    }
    sql = cmd.c_str();
    rc = sqlite3_exec(db,sql,cbCreateTable,0, &ermsg);

    if(rc != SQLITE_OK){
        *log << "Error: " << rc << "\n";
        if(rc == 1){*log << "Table:" << tableName << " already exists.\n";}
        *log << tableName << " could not be created.\n";
    }
    else{
        *log << tableName << " was created.\n";
        *log << "Dimensions: " << cmd << "\n";
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
    cmd+= " " + dimensions;
    cmd+=" VALUES(";
    cmd += info;
    cmd += ");";

    sql = cmd.c_str();
//    cout << cmd << endl;
    rc = sqlite3_exec(db,sql,cbAddToTable,0, &ermsg);

    if(rc != SQLITE_OK){
        *log << "Error: " << rc;
        if(rc == 19){*log << "Item:" << info << " already exists.\n";}
        *log << " Item could not be inserted.\n";
    }
    else{        
        *log << tableName << ": Item was inserted.\n";
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
//    cout << cmd << endl;

    sql = cmd.c_str();

    rc = sqlite3_exec(db,sql,cbDelRow,log, &ermsg);

    if(rc != SQLITE_OK){
        *log << "Error: " << rc;
        *log << tableName << ": Row couldn't be deleted.\n";
    }
    else{
        *log << tableName << " row[ " << index << "] was deleted.\n";
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

    if(rc == SQLITE_ERROR){
        *log << "Error: " << rc;
        *log << tableName << " was accessed.\n";
        *log << "Query wasn't created.\n";
    }
    else{
        *log << "Query created.\n";
    }

    return result;
}

void Table::exp(string col, string op){
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

    ofstream myfile("data.csv");
    string result;
    rc = sqlite3_exec(db,sql,cbExp,(void*)&result, &ermsg);

    myfile << result;
    myfile.close();
//    cout << rc << endl;
    if(rc == SQLITE_ERROR){
        *log << "Error: " << rc;
        *log << tableName << " was accessed.\n";
        *log << "...\n";
        cerr << "no export";
    }
    else{
        cerr << "export";
        *log << "export.\n";
    }

}

void Table::updateTable(string index, string op){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;

    string cmd = "UPDATE ";
    cmd += tableName;
    cmd += " SET ";
    cmd += op;
    cmd += " WHERE ";
    cmd += index;
    cmd += ";";
    sql = cmd.c_str();
//    cout << cmd << endl;
    string result;
    rc = sqlite3_exec(db,sql,cbUpdate,&result, &ermsg);

    if(rc == SQLITE_ERROR){
        *log << "Error: " << rc;
        *log << tableName << " attempted access.\n";
        *log << "Couldn't update.\n";
    }
    else{
        *log << tableName << " was updated.\n";
    }
}

void Table::alterTable(string col, string op){

}

void Table::setDimensions(string newD){dimensions = newD;}

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
    Log * log0 = (Log *)data;
    if(argc < 1){
        *log0 << "Couldn't add to table.\n";
    }
    else{
        *log0 << "Data has been added to table.\n";
    }
    return 0;
}

int Table::cbDelRow(void *data, int argc, char **argv, char **azColName){
    Log * log0 = (Log *)data;
    if(argc < 1){
        *log0 << "Row couldn't be deleted.\n";
    }
    else{
        *log0 << "Row was deleted.\n";
    }
    return 0;
}

int Table::cbCreateQuery(void *data, int argc, char **argv, char **azColName){
    int i;
    string * result = (string *) data;   
    for(i = 0; i < argc; i++){
        if(argv[i] != NULL){*result += argv[i];}
        if(i < argc-1){*result += "|";}}
    *result += "\n";    
    return 0;
}

int Table::cbUpdate(void *data, int argc, char **argv, char **azColName){
    Log * log0 = (Log *)data;
    if(argc < 1){
        *log0 << "Table was not updated.\n";
    }
    else{
        *log0 << "Table was deleted.\n";
    }
    return 0;
}

int Table::cbAlter(void *data, int argc, char **argv, char **azColName){
    Log * log0 = (Log *)data;
    if(argc < 1){
        *log0 << "Table couldn't be altered.\n";
    }
    else{
        *log0 << "Table was altered.\n";
    }
    return 0;
}

int Table::cbExp(void *data, int argc, char **argv, char **azColName){
    string * myfile = (string*)data;
    //prints out columns
    for(int i = 0; i < argc; i++){
        *myfile += azColName[i];
        *myfile += ",";
    }
    *myfile += "\n";
    for(int i = 0; i < argc; i++){
        *myfile += argv[i];
        *myfile +=  ",";
        cout << argv[i] << endl;
    }
    *myfile += "\n";
    cout << *myfile << endl;
}
