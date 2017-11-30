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
    m.configure();

    return 0;
}
