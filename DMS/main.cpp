#include <iostream>
#include "dms.h"
#include "table.h"

using namespace std;

//Testbench DMS file

int main()
{
    /**LOADDATABASE**/

    DMS db("../scada.db", "../configuration_files/deftables_config.txt","../log.txt");

    db.createTable("SampleTable");
    db.createTable("HubTable");
    db.createTable("CalibratedSampleTable");
    db.createTable("CalModTable");

    db.loadDataBase("../testbench_files/SampleTableTB.txt");
    db.loadDataBase("../testbench_files/HubTableTB.txt");
    db.loadDataBase("../testbench_files/CalibrationSampleTableTB.txt");
    db.loadDataBase("../testbench_files/CalModTableTB.txt");

    /**SHOW DATABASE**/

    cout<< "Rawdata larger than 50 " << endl;
    cout << db.getTable("SampleTable")->createQuery("RAWDATA", " RAWDATA > 50") << endl;
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
    cout << db.getTable("SampleTable")->createQuery("TimeStamp,MAX(RAWDATA)", "")<< endl;
    cout<< "\n";
    db.getTable("SampleTable")->exp("*","","../data.txt");

    vector<char*> s = db.getTable("SampleTable")->delimitter("select * from SampleTable");
    for(int i = 0; i < (int)s.size(); i++){cout << s.at(i) <<endl;}
    db.close();
}
