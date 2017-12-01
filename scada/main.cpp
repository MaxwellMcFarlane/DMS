#include "ControlSubSystem/modemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ControlSubSystem/branch.h"
#include "ControlSubSystem/state.h"
#include "../DMS/dms.h"
#include "../DMS/table.h"
using namespace std;

int main()
{

    ModeManager m("../ControlState_config.txt");
    cout << "Mode Manager Configured" << endl;

    DMS db("../scada.db","../configuration_files/deftables_config.txt","../log.txt");
    db.loadDataBase("../testbench_files/StateTableTB.txt");
    db.loadDataBase("../testbench_files/BranchTableTB.txt");
    db.loadDataBase("../testbench_files/ConditionTableTB.txt");

    db.loadDataBase("../testbench_files/SensorTableTB.txt");
    db.loadDataBase("../testbench_files/SensorConfTableTB.txt");
    db.loadDataBase("../testbench_files/CalConfTableTB.txt");

    db.loadDataBase("../testbench_files/SampleTableTB.txt");
    db.loadDataBase("../testbench_files/CalibrationSampleTableTB.txt");
    //cout << db.controlQuery("'volt':null:null:Select RawData from SampleTable where RawData > 0");
    //cout << db.getTable("SampleTable")->isQueryEmpty("Select * from SampleTable");
    ModeManager m("../modeConfig.txt");

    m.configure();
    DMS *dbp=&db;
    cout<<m.currentState<<endl;
    m.nextstate(dbp);
//    cout<<m.currentState<<endl;

        //test for transition
//            State s1("IDLE");
//            State s2("RUN");
//            State s3("FINISH");

//            Branch b1(s2,"'volt':null:null:Select RawData from SampleTable where RawData <0");
//            Branch b2(s3,"'volt':null:null:Select RawData from SampleTable where RawData <60");

//            s1.loadBranch(b1);
//            s1.loadBranch(b2);
//            //cout<<s1.numOfBranches;
//            cout<<"Next state is: "+s1.nextstate(dbp)->name<<endl;

//    return 0;
}
