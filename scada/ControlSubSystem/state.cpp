#include "state.h"
#include "branch.h"
#include "../DMS/dms.h"
#include "../DMS/table.h"
using namespace std;
State::State (string name){
    this->name=name;

}


void State::loadBranch(Branch branch){
    this->branches.push_back(branch);
}

State State::nextstate(DMS *db){
    for(Branch b : this->branches) {
        //throw the condition in the database  with query
        //if the condition has been met return the  next state from the branches
        string tmp = db->getTable("SampleTable")->createQuery("RAWDATA",b.condition);
        if(!tmp.empty()) return *(b.branchState);
    }
    return *this;
}

State::~State(){

}
