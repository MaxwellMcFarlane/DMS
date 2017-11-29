#include "modemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
ModeManager::ModeManager(string fileName)
{
    this->fileName=fileName;

}

ModeManager::~ModeManager()
{

}

State ModeManager::getState(string name){
    for(State s: this->states){
        if(!s.name.compare(name)){
            return s;
        }
    }
    State defaultState("NULL");
    return defaultState;
}
void ModeManager::configure(){
    ifstream file;
    file.open(fileName.c_str());
    if (!file)
        cout<<"CFG: File " + fileName + " couldn't be found!\n";

    string stateDeclaration("STATES:");
    string branchDeclaration("BRANCHES:");
    string line;
    while (!file.eof())
    {
        getline(file,line);

        //cout<<"haha\n";

        if(line.at(0) == '#'){
            //meant for comments
        }
        else if (line.find(stateDeclaration) != std::string::npos) {
            getline(file,line);
            vector<string > stateLine= ModeManager::split(line,',');
            for(string s: stateLine){
                State tempState(s);
                cout<<"CFG: State " +tempState.name + " has been successfully created!\n";
                this->states.push_back(tempState);
            }
        }


        if (line.find(branchDeclaration) != std::string::npos) {


            while(!file.eof()){
                getline(file,line);
                vector<string > branchLine= ModeManager::split(line,',');
                State from= ModeManager::getState(branchLine[0]);
                if(!from.name.compare("NULL")){
                    cout<<"CFG: State " + branchLine[0] + " is not in your state declaration!\n";
                }
                else{
                    State to= ModeManager::getState(branchLine[1]);
                    if(!to.name.compare("NULL")){
                        cout<<"CFG: File " + branchLine[1] + " is not in your state declaration!\n";
                    }
                    else{
                        Branch tempBranch(&to, branchLine[2]);
                        from.loadBranch(tempBranch);
                        cout<<"CFG: A Branch from State " + from.name +" to State " +tempBranch.branchState->name+" with the condition "+tempBranch.condition+" has been successfully loaded!\n";

                    }

                }

            }
        }
    }
    file.close();
    if(!this->states.empty()) this->currentState=&(this->states[0]);
    cout<<"CFG: DONE! State " + this->currentState->name + " is assigned to be the default current state.\n";
}

string  ModeManager::getCurrentState(){
    return this->currentState->name;
}

void ModeManager::nextstate(DMS* db){

    //State temp=this->currentState->nextstate(db);
//    cout<< this->currentState->name+"\n";
//    this->currentState=&temp;
}

vector<string> ModeManager::split(const string s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

