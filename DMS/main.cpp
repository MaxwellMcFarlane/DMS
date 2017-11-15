#include <iostream>
#include "dms.h"
#include "table.h"

using namespace std;

int main()
{
    DMS db("scada.db");
    Log * log;
    log = db.getLog();

    db.createTable("LOOKUP");
    db.createTable("DATA");
    db.createTable("S1");
    db.createTable("S2");    

    db.getTable("LOOKUP")->addToTable("'0xf32'");
    db.getTable("LOOKUP")->addToTable("'0xff2'");
    db.getTable("LOOKUP")->addToTable("'0xfb2'");

    db.getTable("DATA")->addToTable("'0xf32','2:00',13,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xf32','2:23',15,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xf32','2:48',11,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xf32','2:80',22,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xff2','5:41',66,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xff2','6:01',67,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xff2','7:02',69,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xf32','8:45',65,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xff2','11:23',64,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xff2','12:53',63,NULL,NULL");
    db.getTable("DATA")->addToTable("'0xf32','14:35',62,NULL,NULL");

    db.dumpTable("S1");
    db.dumpTable("S2");

    cout<< "Rawdata larger than 500 " << endl;
    cout << db.getTable("DATA")->createQuery("RAWDATA", "RAWDATA > 500") << endl;
    cout<< "\n";
    cout<< "All sensors in architecture" << endl;
    cout << db.getTable("LOOKUP")->createQuery("*", "")<< endl;
    cout<< "\n";
    cout<< "All data collected" << endl;
    cout << db.getTable("DATA")->createQuery("*", "")<< endl;
    cout<< "\n";

    db.getTable("DATA")->updateTable("TS = '2:00'", "CALDATA = 18");
    db.getTable("DATA")->updateTable("TS = '2:00'", "CALMODE = 1");
    db.getTable("DATA")->updateTable("TS > '2:00'", "CALDATA = 34");
    db.getTable("DATA")->updateTable("TS > '2:00'", "CALMODE = 16");

    cout<< "All data collected" << endl;
    cout << db.getTable("DATA")->createQuery("*", "")<< endl;
    cout<< "\n";

    cout<< "All sensors, rawdata, and caldata" << endl;
    cout << db.getTable("DATA")->createQuery("ID,TS,RAWDATA,CALDATA", "")<< endl;
    cout<< "\n";
    cout<< "All last id" << endl; //assuming that id order is shown in value, least to greatest
    cout << db.getTable("DATA")->createQuery("MAX(ID)", "")<< endl;
    cout<< "\n";
    cout<< "Smallest calibrated data point" << endl;
    cout << db.getTable("DATA")->createQuery("MIN(CALDATA)", "")<< endl;
    cout<< "\n";
    cout<< "Largest Rawdata point with time" << endl;
    cout << db.getTable("DATA")->createQuery("TS, MAX(RAWDATA)", "")<< endl;
    cout<< "\n";
    cout<< "Average caldata point with time" << endl;
    cout << db.getTable("DATA")->createQuery("AVG(CALDATA)", "")<< endl;

    db.close();
}
