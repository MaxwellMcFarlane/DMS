#include <iostream>
#include "../src/dms.h"
#include "../src/control/modemanager.h"

using namespace std;

int main()
{
    DMS db("../scada.db", "../configuration_files/deftables_config.txt", "../log.txt");

    db.loadConfigTable("control_config.txt", "../configuration_files/control_config.txt");
    db.loadConfigTable("sensor_config.txt", "../configuration_files/sensor_config.txt");

    db.loadDataBase("../testbench_files/SensorTableTB.txt");
    db.loadDataBase("../testbench_files/SensorConfTableTB.txt");
    db.loadDataBase("../testbench_files/SampleTableTB.txt");
    db.loadDataBase("../testbench_files/CalibrationSampleTableTB.txt");

    try {
        ModeManager m("../configuration_files/control_config.txt", &db);
        m.configure();
        cout << "Loaded states and branches from control_config.txt; starting state: "
             << m.currentState << endl;
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    db.close();
}
