#include <iostream>
#include "dms.h"
#include "table.h"

using namespace std;

int main()
{
    DMS db("scada.db", "../deftables_config.txt");
    Log * log;
    log = db.getLog();

    db.getTable("HubTable")->addToTable("0xf32,'volt'");
    db.getTable("HubTable")->addToTable("0xff2,'volt'");
    db.getTable("HubTable")->addToTable("0xff2,'volt'");
    db.getTable("HubTable")->addToTable("0xfb2,'amp'");
    db.getTable("HubTable")->addToTable("0xfa2,'amp'");
    db.getTable("HubTable")->addToTable("0xfca,'volt'");

    db.getTable("SampleTable")->addToTable("1,'0xf32','2:00',13");
    db.getTable("SampleTable")->addToTable("2,'0xf32','2:23',15");
    db.getTable("SampleTable")->addToTable("3,'0xf32','2:48',11");
    db.getTable("SampleTable")->addToTable("4,'0xf32','2:80',22");
    db.getTable("SampleTable")->addToTable("5,'0xff2','5:41',66");
    db.getTable("SampleTable")->addToTable("6,'0xff2','6:01',67");
    db.getTable("SampleTable")->addToTable("7,'0xff2','7:02',69");
    db.getTable("SampleTable")->addToTable("8,'0xf32','8:45',65");
    db.getTable("SampleTable")->addToTable("9,'0xff2','11:23',64");
    db.getTable("SampleTable")->addToTable("10,'0xff2','12:53',63");
    db.getTable("SampleTable")->addToTable("11,'0xf32','14:35',62");

    db.getTable("CalibratedSampleTable")->addToTable("1,'5:41',66,1");
    db.getTable("CalibratedSampleTable")->addToTable("2,'6:01',67,1");
    db.getTable("CalibratedSampleTable")->addToTable("3,'7:02',69,1");
    db.getTable("CalibratedSampleTable")->addToTable("4,'8:45',65,1");
    db.getTable("CalibratedSampleTable")->addToTable("5,'11:23',64,1");
    db.getTable("CalibratedSampleTable")->addToTable("6,'12:53',63,1");
    db.getTable("CalibratedSampleTable")->addToTable("7,'14:35',62,1");

    db.getTable("CalModTable")->addToTable("2,17,'volt','ß'");
    db.getTable("CalModTable")->addToTable("3,17,'volt','∂'");
    db.getTable("CalModTable")->addToTable("4,17,'volt','∂'");
    db.getTable("CalModTable")->addToTable("5,17,'volt','ƒ'");
    db.getTable("CalModTable")->addToTable("6,17,'volt','å'");
    db.getTable("CalModTable")->addToTable("7,17,'volt','∆'");

    cout<< "Rawdata larger than 50 " << endl;
    cout << db.getTable("SampleTable")->createQuery("RAWDATA", "RAWDATA < 100") << endl;
    if(db.getTable("SampleTable")->createQuery("RAWDATA", "RAWDATA < 100") == ""){cout << "hello" << endl;}
    cout<< "\n";
    cout<< "All sensors in architecture" << endl;
    cout << db.getTable("HubTable")->createQuery("*", "")<< endl;
    cout<< "\n";
    cout<< "All data collected" << endl;
    cout << db.getTable("CalModTable")->createQuery("*", "")<< endl;
    cout<< "\n";

    db.getTable("CalModTable")->updateTable("Type = 'volt'", "ModelNumber = 18");
    db.getTable("CalModTable")->updateTable("Type = 'amp'", "ModelNumber = 5");

    cout<< "All data collected" << endl;
    cout << db.getTable("CalModTable")->createQuery("*", "")<< endl;
    cout<< "\n";

    cout<< "All sensors, rawdata, and caldata" << endl;
    cout << db.getTable("SampleTable")->createQuery("SensorID,TimeStamp,RAWDATA", "")<< endl;
    cout<< "\n";
    cout<< "All last id" << endl; //assuming that id order is shown in value, least to greatest
    cout << db.getTable("SampleTable")->createQuery("MAX(SensorID)", "")<< endl;
    cout<< "\n";    
    cout<< "Largest Rawdata point with time" << endl;
    cout << db.getTable("SampleTable")->createQuery("TimeStamp, MAX(RAWDATA)", "")<< endl;
    cout<< "\n";
    db.getTable("SampleTable")->exp("*","");
    db.close();
}
