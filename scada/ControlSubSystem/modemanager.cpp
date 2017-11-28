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

State* ModeManager::getState(string name){
    for(State s: this->states){
        if(s.name.compare(name)) return &s;
    }
    return NULL;

}
void ModeManager::configure(){
    ifstream file;
    file.open(fileName.c_str());
    if (!file)
        cout<<"CFG: File " + fileName + " couldn't be found!\n";

    string line;
    while (!file.eof())
    {
        getline(file,line);
        string stateDeclaration("#STATE");
        string branchDeclaration("#BRANCH");


        if(line.at(0) == '#'){

        }
        else{


            vector<string > stateLine= ModeManager::split(line,',');

            for(string s: stateLine){
                State tempState(s);
                cout<<"State  " +tempState.name + " created\n";
                this->states.push_back(tempState);
            }
        }
        //}

        //        if(temp.find_first_of(branchDeclaration)!= temp.npos){

        //            while(!file.eof()){
        //                string newLine=line;
        //                vector<string > branchLine= ModeManager::split(newLine,',');
        //                State *fromState= getState(branchLine[0]);
        //                if(!fromState){
        //                    cout<<"CFG: File " + branchLine[0] + " couldn't be found in your state declaration!\n";
        //                }
        //                else{
        //                    State *toState= getState(branchLine[0]);
        //                    if(!toState){
        //                        cout<<"CFG: File " + branchLine[1] + " couldn't be found in your state declaration!\n";
        //                    }
        //                    else{
        //                        Branch tempBranch(toState, branchLine[2]);
        //                        fromState->loadBranches(tempBranch);
        //                    }
        //                }

        //            }
        //        }
    }

    file.close();
}

string  ModeManager::getCurrentState(){
    return this->currentState->name;
}

void ModeManager::reconfigure(){

    // when currentstate has been updated, alert the collection manager to reconfigure

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

