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

State* State::nextstate(int condition){
    if(condition==1) {
        cout<< "next";
        return this->branches[0].branchState;
    }
    else return this;
//    for(Branch b : this->branches) {
//        //throw the condition in the database  with query
//        //if the condition has been met return the  next state from the branches
//        //string tmp = db->getTable("SampleTable")->createQuery("RAWDATA",b.condition);
//        //        cout << b.condition << endl;
//        //        cout << db->controlQuery(b.condition) << endl;
//        if(db->controlQuery(b.condition) ) return *(b.branchState);
//    }
//    return *this;
}

State::~State(){

}
