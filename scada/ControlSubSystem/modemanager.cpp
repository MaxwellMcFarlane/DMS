#include "modemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


ModeManager::ModeManager(string fileName, DMS *db)
{
    //store
    this->fileName=fileName;
    this->db=db;
}

ModeManager::~ModeManager()
{

}

State* ModeManager::getState(string name){
    for(int i=0;i< states.size();i++){
        if(!states[i].name.compare(name)){
            return &states[i];// the name matches return the pointer to this state
        }
    }
    State defaultState("NULL");//the name is not found in the states list return a NULL name state
    return &defaultState;
}

void ModeManager::configure(){
    ifstream file;
    int lineCount=0;
    file.open(fileName.c_str());
    errorLog->trunc_file();//configure is called clear any preexisiting error log files
    log->trunc_file();//configure is called clear any preexisiting  log files


    if (!file){
        //file not found
        *log<<"CFG: File " + fileName + " couldn't be found!\n";
        *errorLog<<"CFG: File " + fileName + " couldn't be found!\n";
        throw runtime_error("CFG: File " + fileName + " couldn't be found!\n");
    }

    //Look for "STATES:" in a line, when found declare STATES
    string stateDeclaration("STATES:");
    //Look for "BRANCHES:" in a line, when found declare BRANCHES
    string branchDeclaration("BRANCHES:");
    string line;

    while (!file.eof())
    {
        //iterate till the end of the file

        lineCount++;//line counter
        getline(file,line);//iterator by line

        if(line.at(0)=='E' && line.at(1)=='N' && line.at(2)=='D') break;// this triggers an end to the script
        if(line.at(0) == '#')  continue; // # is for commenting;


        else if (line.find(stateDeclaration) != std::string::npos) {
            //state declaration block
            getline(file,line);
            vector<string > stateLine= ModeManager::split(line,',');//split lines
            for(string s: stateLine){

                State tempState(s);//create a state
                *log<<"CFG: State " +tempState.name + " has been successfully created!\n";
                states.push_back(tempState);//add the state to the states list
                db->getTable("StateTable")->addToTable("'"+s+"'");//add the state to the statetable in the dms
            }
        }


        if (line.find(branchDeclaration) != std::string::npos)
        {
            //branch declaration block

            while(!file.eof())
            {

                //iterate till end of the file
                lineCount++;
                getline(file,line);
                if(line.at(0)=='E' && line.at(1)=='N' && line.at(2)=='D') break;
                if(line.at(0) == '#') continue;// # is for commenting
                else{
                    lineCount++;//increment the line number
                    vector<string > branchLine= ModeManager::split(line,',');
                    if(branchLine.size()>3){
                        //more than 3 parameter errors
                        *errorLog<<"CFG_ERROR: In line number "<<lineCount<<" you gave "+to_string(branchLine.size()) +" parameters. The branch declaration is expecting 3 parameters: STATE_FROM,STATE_TO,CONDITION!\n";
                        throw runtime_error("CFG_ERROR: parameter list more than 3");
                    }
                    else{
                        string from=ModeManager::getState(branchLine[0])->name;
                        //the first string in the line represents the state from where the branch starts

                        if(!from.compare("NULL")){
                            //undeclared state error
                            *log<<"CFG_ERROR: State " + branchLine[0] + " is not in your state declaration!\n";
                            *errorLog<<"CFG_ERROR: State " + branchLine[0] + " is not in your state declaration!\n";
                            throw runtime_error("CFG_ERROR: State " + branchLine[0] + " is not in your state declaration!\n");
                        }
                        else{
                            string to= ModeManager::getState(branchLine[1])->name;
                            if(!to.compare("NULL")){
                                //undeclared state error

                                *log<<"CFG_ERROR: File " + branchLine[1] + " is not in your state declaration!\n";
                                *errorLog<<"CFG_ERROR: File " + branchLine[1] + " is not in your state declaration!\n";
                                throw runtime_error("CFG_ERROR: File " + branchLine[1] + " is not in your state declaration!\n");

                            }
                            else{
                                Branch tempBranch( getState( branchLine[1]),prepQuery(branchLine[2]));//create a branch
                                db->getTable("BranchTable")->addToTable("'"+from+"' , '"+to+"' , '"+branchLine[2]+"'");//add the branch to the DMS

                                for(int i=0;i< states.size();i++){
                                    if(!branchLine[0].compare(states[i].name)) states[i].loadBranch(tempBranch);//add the branch to state_from

                                }

                                *log<<"CFG: A Branch from State " + from +" to State " + tempBranch.branchState->name +" with the condition "+tempBranch.condition+" has been successfully loaded!\n";
                            }

                        }
                    }

                }

            }
        }
        if(line.at(0)=='E' && line.at(1)=='N' && line.at(2)=='D') break;// END triggers an end to the script
    }
    file.close();
    if(!states.empty()) {
        currentState=(states[0]).name;
        db->setCurrentState(currentState);//update the dms
        //set the first state to be the default currentstate
        *log<<"CFG: DONE! State " + currentState + " is assigned to be the default current state.\n";
    }
}



void ModeManager::nextstate(){
    for(int i=0;i< states.size();i++){
        if(!states[i].name.compare(currentState)){
            //check if the next state branch can be taken
            *log<<"Now currrentState is: "+states[i].nextstate(db)+"\n";
            currentState=states[i].nextstate(db);//set whateever you got from the nextstate call to the current state
            db->setCurrentState(currentState);//update the currentstate in the dms
            break;
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

string ModeManager::prepQuery(string condition){
    vector<string> tokens=split(condition,':');
    string str("'");
    str.append(tokens[0]);
    str.append("'");
    str.append(":");
    str.append(tokens[1]);
    return str;
}
