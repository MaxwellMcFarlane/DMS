#include <iostream>
#include "ControlSubSystem/branch.h"
#include "ControlSubSystem/state.h"
#include "../DMS/dms.h"
#include "../DMS/table.h"
using namespace std;

int main()
{
    DMS db("test.db", "../deftables_config.txt");
    DMS *db_pointer=&db;
    Log * log;
    log = db.getLog();

    db.getTable("SampleTable")->addToTable("1,'0xf32','2:00',13");
    db.getTable("SampleTable")->addToTable("2,'0xf32','2:23',15");
    db.getTable("SampleTable")->addToTable("3,'0xf32','2:48',11");
   db.getTable("SampleTable")->addToTable("4,'0xf32','2:80',22");

    //condition queried by modemanager is that rawdata is greater than 30
    string s = db.getTable("SampleTable")->createQuery("RAWDATA","RAWDATA > 30");


    State s0("IDLE");
    State s1("RUN_1");
    State s2("RUN_2");
    State s3("FINALIZE");
//    State *p0=&s0;
//    State *p1=&s1;
//    State *p2=&s2;
//    State *p3=&s3;

    Branch b1(s1,"RAWDATA > 20");
    Branch b2(s2,"RAWDATA < 20");
    Branch b3(s3,"RAWDATA ==64");
    Branch b4(s3,"RAWDATA ==64");
    Branch b5(s0,"RAWDATA > 64");

    s0.loadBranches(b1);
    s0.loadBranches(b2);

    s1.loadBranches(b3);
    s2.loadBranches(b4);

    s3.loadBranches(b5);



    cout<< "NOW IN STATE:"+ (s0.nextstate(db_pointer)).name<<endl;



    return 0;
}
