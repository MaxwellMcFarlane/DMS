#include "modemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

ModeManager::ModeManager(){}

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
            //State *p=&s;
            return s;
        }
    }
    State defaultState("NULL");
    //State* dfp=&defaultState;
    return defaultState;
}

void ModeManager::configure(){
    ifstream file;
    file.open(fileName.c_str());
    if (!file)
        cout<<"CFG: File " + fileName + " couldn't be found!\n";
    int i=0;
    string stateDeclaration("STATES:");
    string branchDeclaration("BRANCHES:");
    string line;    
    while (!file.eof())
    {
        getline(file,line);
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
<<<<<<< HEAD

            while(!file.eof()){
                getline(file,line);
                vector<string > branchLine= ModeManager::split(line,',');
                string from=ModeManager::getState(branchLine[0]).name;

                if(!from.compare("NULL")){
=======
            while(!file.eof()){
                getline(file,line);                
                vector<string> branchLine= ModeManager::split(line,',');
                State from= ModeManager::getState(branchLine[0]);
                if(!from.name.compare("NULL")){
>>>>>>> refs/remotes/origin/master
                    cout<<"CFG: State " + branchLine[0] + " is not in your state declaration!\n";
                }
                else{
                    string to= ModeManager::getState(branchLine[1]).name;
                    if(!to.compare("NULL")){
                        cout<<"CFG: File " + branchLine[1] + " is not in your state declaration!\n";
                    }
                    else{
                        Branch tempBranch(ModeManager::getState(branchLine[1]), branchLine[2]);
                        ModeManager::getState(branchLine[0]).loadBranch(tempBranch);
                        cout<<"CFG: A Branch from State " + from +" to State " + to +" with the condition "+tempBranch.condition+" has been successfully loaded!\n";
                    }

                }
            }

        }
    }
    file.close();
    if(!this->states.empty()) {
        this->currentState=(this->states[0]).name;
        cout<<"CFG: DONE! State " + this->currentState + " is assigned to be the default current state.\n";

    }
}



void ModeManager::nextstate(DMS* db){
    string temp=currentState;
    string a=ModeManager::getState(temp).nextstate(db)->name;
    //this->currentState=ModeManager::getState(temp).nextstate(db)->name;
    cout<<a<<endl;
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

