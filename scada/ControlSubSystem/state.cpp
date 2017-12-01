#include "state.h"
#include "branch.h"
#include "../DMS/dms.h"
#include "../DMS/table.h"
using namespace std;
State::State (string name){
    this->name=name;
     this->numOfBranches=0;
}


void State::loadBranch(Branch branch){
    numOfBranches++;

    this->branches.push_back(branch);

}

State* State::nextstate(DMS* db){
    cout<<this->numOfBranches<<endl;
    for(Branch b : this->branches) {
        //throw the condition in the database  with query
        //if the condition has been met return the  next state from the branches
        bool a=db->controlQuery(b.condition);
        cout<< a<<endl;
        if(a ) {cout<< "ha"<<endl;return (b.branchState);}
    }
    return this;
}

State::~State(){

}
