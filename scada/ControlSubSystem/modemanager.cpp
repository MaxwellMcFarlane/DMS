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
<<<<<<< HEAD

    for(State s: states){

=======
    for(State s: this->states){
>>>>>>> refs/remotes/origin/master
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
    int lineCount=0;
    file.open(fileName.c_str());
    log->trunc_file();
    if (!file){
        cout<<"CFG: File " + fileName + " couldn't be found!\n";
        *log<<"CFG: File " + fileName + " couldn't be found!\n";
    }
    string stateDeclaration("STATES:");
    string branchDeclaration("BRANCHES:");
    string line;
    while (!file.eof())
    {
        lineCount++;
        getline(file,line);

        if(line.at(0) == '#'){
            // # is for commenting

        }
        else if (line.find(stateDeclaration) != std::string::npos) {
            getline(file,line);
            vector<string > stateLine= ModeManager::split(line,',');
            for(string s: stateLine){
                State tempState(s);
                cout<<"CFG: State " +tempState.name + " has been successfully created!\n";

                states.push_back(tempState);
            }
        }


        if (line.find(branchDeclaration) != std::string::npos) {

            while(!file.eof()) {
                lineCount++;
                getline(file,line);
                if(line.at(0) == '#'){
                    // # is for commenting

                }
                else{
                    lineCount++;
                    vector<string > branchLine= ModeManager::split(line,',');
                    if(branchLine.size()>3){
                        cout<<"CFG_ERROR: In line number "<<lineCount<<" you gave "<<branchLine.size() <<" parameters. The branch declaration is expecting 3 parameters: STATE_FROM,STATE_TO,CONDITION!"<<"\n";
                        *log<<"\n";
                    }
                    else{
                        string from=ModeManager::getState(branchLine[0]).name;

                        if(!from.compare("NULL")){
                            cout<<"CFG_ERROR: State " + branchLine[0] + " is not in your state declaration!\n";
                            *log<<"CFG_ERROR: State " + branchLine[0] + " is not in your state declaration!\n";
                        }
                        else{
                            string to= ModeManager::getState(branchLine[1]).name;
                            if(!to.compare("NULL")){
                                cout<<"CFG_ERROR: File " + branchLine[1] + " is not in your state declaration!\n";
                                *log<<"CFG_ERROR: File " + branchLine[1] + " is not in your state declaration!\n";

                            }
                            else{
                                Branch tempBranch( getState( branchLine[1]), branchLine[2]);
                                for(int i=0;i< states.size();i++){
                                    if(!states[i].name.compare(branchLine[0])) states[i].loadBranch(tempBranch);
                                }
                                cout<<"CFG: A Branch from State " + from +" to State " + tempBranch.branchState->name +" with the condition "+tempBranch.condition+" has been successfully loaded!\n";
                            }

                        }
                    }

                }
            }
        }
    }
    file.close();
    if(!states.empty()) {
        currentState=(states[0]).name;
        cout<<"CFG: DONE! State " + currentState + " is assigned to be the default current state.\n";
    }
}



void ModeManager::nextstate(DMS* db){
    for(int i=0;i< states.size();i++){
        if(!states[i].name.compare(currentState)){

            currentState=states[i].nextstate(db);
             cout<<states[i].nextstate(db)<<endl;
        }
    }

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

