#ifndef BRANCHES_H
#define BRANCHES_H
#include <iostream>
#include "state.h"
using namespace std;

class State;

class Branch{
public:
    State *branchState;
    string condition;

     Branch (State branchState, string condition );
    ~Branch();
};


#endif // BRANCHES_H
