#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <vector>
#include "branch.h"
using namespace std;

class Branch;

class State{
     public:
     string name;
     vector<Branch> branches;
     int numOfBranches;
     State(string name);
     void loadBranches(Branch branch);
     State nextstate(string condition );
     ~State();

};

#endif // STATE_H
