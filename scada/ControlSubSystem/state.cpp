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

string State::nextstate(DMS* db){

    for(int i=0; i< branches.size();i++) {
        bool a=db->controlQuery(branches[i].condition);

        if(a){
            cout<<branches[i].branchState->name<<endl;
            return (branches[i].branchState->name);

        }
    }
    return this->name;
}

State::~State(){

}
