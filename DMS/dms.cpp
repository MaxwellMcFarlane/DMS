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
    //allow system to accept foreign keys
    rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    cout << rc << endl;
    if(rc == SQLITE_OK){
        *log << "DataBase " << filename << " is opened.\n";
    }
    else{
        *log <<"Error: " << rc << " has occured.\n";
    }

    string tableName,dimensions,dummy;
    ifstream myconfig(dbConfig);

    if(myconfig.is_open()){
        while(!myconfig.eof()){
            //searches for the next chunk of text
            while(tableName.empty()){getline(myconfig,tableName);}
            getline(myconfig,tableName);
            //gets the list of dimensions
            while(dummy != "*"){dimensions += dummy;getline(myconfig,dummy);}
//            getline(myconfig,dimensions);
            createTable(tableName,dimensions);
            getline(myconfig,dimensions);
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
    //allow system to accept foreign keys
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    cout << rc << endl;
    if(rc == SQLITE_OK){
        *log << "DataBase " << filename << " is opened.\n";
    }
    else{
        *log <<"Error: " << rc << " has occured.\n";
    }
}

DMS::DMS(string name, string dbConfig, string logPath){    
    int rc = 0;
//    char *ermsg = 0;
    log = new Log(logPath);
    time_t now = time(0);
    string dt = ctime(&now);

    *log << "\n" << dt;

    filename = name.c_str();
    rc = sqlite3_open(name.c_str(),&db);
    //allow system to accept foreign keys
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    if(rc == SQLITE_OK){
        *log << "DataBase " << filename << " is opened.\n";
    }
    else{
        *log <<"Error: " << rc << " has occured.\n";
    }
    createTable("ConfigFileTable","(configID INTEGER PRIMARY KEY AUTOINCREMENT, Configuration TEXT);");
    getTable("ConfigFileTable")->setDimensions("Configuration");
    string tableName,dimensions,dummy;;
    ifstream myconfig(dbConfig);

    if(myconfig.is_open()){
        while(!myconfig.eof()){
            //searches for the next chunk of text
            while(tableName.empty()){getline(myconfig,tableName);}
            //gets the list of dimensions
            while(dummy != "*"){dimensions += dummy;getline(myconfig,dummy);}
            //creates table
            createTable(tableName,dimensions);
            getTable("ConfigFileTable")->addToTable("'" + tableName + " " + dimensions + "'");
            getline(myconfig,dimensions);
            //sets dimensions to a usable format
            getTable(tableName)->setDimensions(dimensions);
            //reset parsing variables            
            tableName = "";
            dimensions = "";
            dummy = "";
        }
        myconfig.close();
    }
    else{*log << "Unable to open file.\n"; cerr << "Unable to open file.\n";}
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
    return 0;
}

void DMS::dumpTable(string tableName){
    int rc = 0;
    char *ermsg = 0;
    const char * sql;
    string cmd = "DROP TABLE ";
    cmd += tableName;
    cmd += ";";
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

vector<char*> DMS::delimitter(string cmd){
    vector<char*> k;
    char * it;
    it = strtok((char*)cmd.c_str(), ",");
    while(it != NULL){
        k.push_back(it);
        it = strtok(NULL, ",");
    }

    return k;
}

Log* DMS::getLog(){return log;}

void DMS::getNewLog(){log = new Log();}

void DMS::loadDataBase(string myfilePath){
    ifstream myfile(myfilePath);
    string tableName;
    string data;
    if(myfile.is_open()){
        getline(myfile,tableName);                
        if(getTable(tableName) != 0){
            while(!myfile.eof()){
                getline(myfile,data);
                getTable(tableName)->addToTable(data);
            }
        }
        else{*log << "Table Retrieval Error.\n";}
        myfile.close();
        }
    else{*log << "Unable to load data.\n"; cerr << "Unable to open file.\n";}
}

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
    (void)argv;
    return 0;
}






