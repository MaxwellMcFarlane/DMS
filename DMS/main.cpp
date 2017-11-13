#include <iostream>
#include "dms.h"
#include "table.h"

using namespace std;

int main()
{
    DMS db("scada.db");
    db.createTable("LOOKUP");
    db.createTable("S0");
    db.createTable("S1");
    db.createTable("S2");
    db.createTable("S3");
    db.createTable("S4");
    db.createTable("S5");
    db.createTable("S6");
    db.createTable("S7");
    db.createTable("S8");

    db.getTable("LOOKUP")->addToTable("1");
    db.getTable("LOOKUP")->addToTable("2");
    db.getTable("LOOKUP")->addToTable("3");
    db.getTable("LOOKUP")->addToTable("4");
    db.getTable("LOOKUP")->addToTable("5");
    db.getTable("LOOKUP")->addToTable("6");
    db.getTable("LOOKUP")->addToTable("7");
    db.getTable("LOOKUP")->addToTable("8");

    db.getTable("S2")->addToTable("1,2,1,5,1");
    db.getTable("S0")->addToTable("1,1,1,1,1");
    db.getTable("S0")->addToTable("2,5,1,1,1");
    db.getTable("S0")->addToTable("3,1,2,1,4");
    db.getTable("S0")->addToTable("4,1,6,1,1");
    db.getTable("S0")->addToTable("5,1,6,1,1");
    db.getTable("S0")->addToTable("6,1,6,1,1");
    db.getTable("S0")->addToTable("7,1,6,1,1");
    db.getTable("S0")->addToTable("8,1,6,1,1");
    db.getTable("S0")->addToTable("9,1,6,1,1");
    db.getTable("S0")->addToTable("10,1,6,1,1");

    db.dumpTable("S3");
    db.dumpTable("S2");

    db.getTable("S0")->createQuery("RAWDATA", "RAWDATA > 2");
    db.getTable("LOOKUP")->createQuery("*", "");
    db.getTable("S0")->createQuery("*", "");
    db.getTable("S0")->createQuery("ID,RAWDATA,CALDATA", "");
    db.getTable("S0")->createQuery("MAX(ID)", "");
    db.getTable("S0")->createQuery("MIN(RAWDATA)", "");
    db.getTable("S0")->createQuery("MAX(TS)", "");
}
