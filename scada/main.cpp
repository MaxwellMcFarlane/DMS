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
<<<<<<< HEAD
    ModeManager m("../modeConfig.txt");
    m.configure();


=======
    DMS db("test1.db", "../deftables_config.txt");
    DMS *db_pointer=&db;
    Log * log;
    log = db.getLog();

    db.getTable("SampleTable")->addToTable("1,'0xf32','2:00',13");
    db.getTable("SampleTable")->addToTable("2,'0xf32','2:23',15");
    db.getTable("SampleTable")->addToTable("3,'0xf32','2:48',11");

    db.getTable("SampleTable")->addToTable("4,'0xf32','2:80',22");

    //condition queried by modemanager is that rawdata is greater than 30
   // string s = db.getTable("SampleTable")->createQuery("RAWDATA","RAWDATA > 30");
>>>>>>> f4f06c188ef0d32c799df773f42d3f5d1502c3c1

}
