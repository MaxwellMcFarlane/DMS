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
    m.nextstate(dbp);

    State s1("STOP");
    State s2("RUN");

    Branch b1(&s2,"2");
    Branch b2(&s1,"1");

    s1.loadBranch(b1);
    s2.loadBranch(b2);

    cout<<s1.nextstate(1)->name<<endl;

    return 0;
}
