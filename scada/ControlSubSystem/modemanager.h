#ifndef MODEMANAGER_H
#define MODEMANAGER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "branch.h"
#include "state.h"
#include "../DMS/dms.h"
#include "../DMS/table.h"
#include "../tools/log.h"
class ModeManager
{

public:
    string fileName;
    vector<State> states;
    string currentState;
    ModeManager(string fileName);
    ModeManager();
    State getState(string name);
    void configure();
    string  getCurrentStateName();
    void nextstate(DMS *db);
    ~ModeManager();
    vector<string> split(const string s, char delimiter);
    Log * log = new Log("../stateError.txt");


};

#endif // MODEMANAGER_H
