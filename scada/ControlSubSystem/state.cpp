#include "state.h"
#include "branch.h"
using namespace std;
State::State (string name){
    this->name=name;

}
void State::loadBranches(Branch branch){
    this->branches.push_back(branch);
}
State State::nextstate(string condition ){
    for(Branch b : this->branches) {
        //throw the condition in the database  with query
        //if the condition has been met return the  next state from the branches
        // return branches[i].state;
    }
    return *(branches[0].branchState);
}

State::~State(){

}
