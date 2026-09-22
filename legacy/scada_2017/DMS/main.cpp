/*
Author: Maxwell McFarlane

*/



#include <iostream>
#include "dms.h"
#include "table.h"

using namespace std;
static DMS db("../scada.db", "../configuration_files/deftables_config.txt","../log.txt");
//Testbench DMS file

void testSampleTable();
void testQueries();
void testCalTable();
void testResetRowID();
void testTableFnc();
void testMultiQuery();
void testExport();
void testClrTable();


int main()
{
    /**LOADDATABASE**/    
    
    //order is very important here because tables are constrained by others
    db.loadDataBase("../testbench_files/StateTableTB.txt");
    db.loadDataBase("../testbench_files/BranchTableTB.txt");
    db.loadDataBase("../testbench_files/ConditionTableTB.txt");

    db.loadDataBase("../testbench_files/SensorTableTB.txt");
    db.loadDataBase("../testbench_files/SensorConfTableTB.txt");
    db.loadDataBase("../testbench_files/CalConfTableTB.txt");

    db.loadDataBase("../testbench_files/SampleTableTB.txt");    
    db.loadDataBase("../testbench_files/CalibrationSampleTableTB.txt");   

    db.loadConfigTable("control_config.txt","/Users/maxwellmcfarlane/scada_repo/configuration_files/control_config.txt");
    db.loadConfigTable("sensor_config.txt","/Users/maxwellmcfarlane/scada_repo/configuration_files/sensor_config.txt");

    //Call tests
    testSampleTable();
    testQueries();
    testCalTable();
    testResetRowID();
    testTableFnc();
    testMultiQuery();
    testExport();
    testClrTable();

    db.close();
}

void testQueries(){
    cout << db.controlQuery("'s0':Select RawData from SampleTable where RawData > 60") << endl;
    cout << db.controlQuery("null : 		3890: 		1: 		Select RawData from SampleTable where RawData > 30") << endl;

}


void testSampleTable(){

    cout<< "Rawdata larger than 50 " << endl;
    cout << db.getTable("SampleTable")->createQuery("RAWDATA", "") << endl;
    cout << db.getTable("SampleTable")->createQuery("SAMPLEID", "") << endl;
    cout<< "\n";
    cout<< "All sensors in architecture" << endl;
    cout << db.getTable("HubTable")->createQuery("*", "")<< endl;
    cout<< "\n";
    cout<< "All data collected" << endl;


    vector<char*> s = db.getTable("SampleTable")->delimitter("select * from SampleTable");
    for(int i = 0; i < (int)s.size(); i++){cout << s.at(i) <<endl;}
    cout << db.getTableHeaders("SensorTable") << endl;
    cout<< db.isSensorExist("'s0'") << endl;
    db.getTableHeaders("StateTable");

}

void testMultiQuery(){
    db.getTable("SampleTable")->addMultiToTable("'s0',2,3\n's0',2,3\n's0',2,3\n's0',2,3\n's0',2,3\n's0',2,3\n's0',2,3\n's0',2,3\n's0',2,3\n");
}

void testTableFnc(){
    cout<< "All sensors, rawdata, and caldata" << endl;
    cout << db.getTable("SampleTable")->createQuery("SensorID,TimeStamp,RAWDATA", "")<< endl;
    cout<< "\n";
    cout<< "All last id" << endl; //assuming that id order is shown in value, least to greatest
    cout << db.getTable("SampleTable")->createQuery("MAX(SensorID)", "")<< endl;
    cout<< "\n";
    cout<< "Largest Rawdata point with time" << endl;
    cout << db.getTable("SampleTable")->createQuery("TimeStamp,MAX(RAWDATA)", "")<< endl;
    cout<< "\n";
}

void testExport(){
    db.getTable("SampleTable")->exp("*","","../data.csv");
    db.getTable("SampleTable")->exp("TimeStamp,RawData","RawData > 200","../data2.csv");
    db.getTable("HubTable")->exp("*","","../data1.csv");
}

void testCalTable(){
    cout << db.getTable("CalModTable")->createQuery("*", "")<< endl;
    cout<< "\n";

    //Change Calibration Data in Database
    db.getTable("CalModTable")->updateTable("Type = 'volt'", "ModelNumber = 18");
    db.getTable("CalModTable")->updateTable("Type = 'amp'", "ModelNumber = 5");

    //Print new Data in Calibration table
    cout<< "All data collected" << endl;
    cout << db.getTable("CalModTable")->createQuery("*", "")<< endl;
    cout<< "\n";

}

void testResetRowID(){
    db.resetRowIdTable("StateTable","rowid");
}

void testClrTable(){
    db.clearTable("SampleTable");
}