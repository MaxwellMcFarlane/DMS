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
class ModeManager
{

public:
    string fileName;
    vector<State> states;
    State* currentState;
    ModeManager(string fileName);
    State getState(string name);
    void configure();
    string  getCurrentState();
    void nextstate();
    ~ModeManager();
    vector<string> split(const string s, char delimiter);

};

#endif // MODEMANAGER_H
