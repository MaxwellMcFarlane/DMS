#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <vector>
#include "branch.h"
#include "../DMS/dms.h"
#include "../DMS/table.h"
using namespace std;

class Branch;

class State{
     public:
     string name;
     vector<Branch> branches;
     int numOfBranches;
     State(string name);
     void loadBranch(Branch branch);
     State nextstate(DMS *db);
     ~State();

};

#endif // STATE_H
