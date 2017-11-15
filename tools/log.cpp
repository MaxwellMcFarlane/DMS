#include "log.h"
#include "macros.h"

/**
 * @author: Maxwell McFarlane
 * @version: 1.0
 * Description:
 * <p>
 * The file name is established and
 * the file stream is opened at a default appending mode
 * meanging that the user will initially retain previous information. However,
 * this program allows the user to switch between append mode and truncate mode
 * so that no information is not permanently lost while the program is running.
 * <p>
 * @param:std::string fileName, the name of the file, gets stored
**/

Log::Log() {
    SHOW_WHERE;
    this->fileName = "default.txt";
    fh.open(fileName, std::ofstream::app);
}


Log::Log(std::string fileName) {
    SHOW_WHERE;
    this->fileName = fileName;
    fh.open(fileName, std::ofstream::app);
}

Log::Log(Log &obj) {
    SHOW_WHERE;
    this->fileName = obj.fileName;
    fh.open(fileName, std::ofstream::app);
}

// In the destructor the file handler is closed.
Log::~Log() {
    remove("temporary_mem.txt");
    remove("temporary_mem2.txt");
    fh.close();
}

/**
 * Description:A set of overloaded operators.
 * <p>
 * This set is made to the increase the flexibility of the ouput operator.
 * Each one is made for different several potential data types.
 * <p>
**/
Log& Log::operator<<(std::string str) {fh << str; fh.flush(); return *this;}
Log& Log::operator<<(int data)        {fh << data; fh.flush();return *this;}
Log& Log::operator<<(float data)      {fh << data; fh.flush();return *this;}
Log& Log::operator<<(double data)     {fh << data; fh.flush();return *this;}
Log& Log::operator<<(long data)       {fh << data; fh.flush();return *this;}

void Log::operator =(Log &obj){some_data = obj.some_data;}
/**
 * Description:
 * This method allows the user to switch to append mode. If the filehandle was origianlly
 * in truncate mode the method copies back the information to the test.txt file from
 * the tmp file.
 * @return: boolean that determines if the program succesfully switched to append mode
**/
bool Log::app_file(){

    if(fh.is_open()){
        //to copy back lost information from switching to truncate mode
        //this method returns the info on the tmp.txt back to the original test.txt file
        if(!app){
            //in case the user is switching after logging information already
            //then the program will store that info in mid and append after tst had been copied onto
            std::ifstream  src("temporary_mem.txt", std::ios::in);
            std::fstream  mid("temporary_mem2.txt",  std::ios::out);
            std::fstream  tst(fileName, std::ios::in);

            //tmp save data written
            mid << tst.rdbuf();
            mid.close();
            tst.close();

            //replace with previous save
            tst.open(fileName, std::ios::out);
            tst << src.rdbuf();
            src.close();
            tst.close();

            //append tmp save data
            mid.open("temporary_mem2.txt",  std::ios::in);
            tst.open(fileName, std::ios::out  | std::ios::app);
            tst << mid.rdbuf();
            mid.close();
            tst.close();

            remove("temporary_mem.txt");
            remove("temporary_mem2.txt");
            fh.close();
            fh.open(fileName,std::ofstream::out | std::ofstream::app);
            app = true;
            return true;
        }
        else{std::cout<< "Already Appending"<<endl;}
    }
    app = true;
    return false;
}
/**
 * Description:
 * This method allows the user to switch to truncate mode. If the filehandle was origianlly
 * in append mode the method copies the information to the tmp.txt file from
 * the test.txt file, so that the program doesn't lose the information in it.
 * @return: boolean that determines if the program succesfully switched to truncate mode
**/
bool Log::trunc_file(){
    //checks to see if the fstream is still open
    if(curr_state()){
        //to prevent the data from the file from permanantly getting deleted
        //the method checks if it was appending and saves the contents in the tmp.txt file
        if(app){
            //saves the file content
            std::ifstream  src(fileName, std::ios::in);
            std::ofstream  dst("temporary_mem.txt",   std::ios::out);
            dst << src.rdbuf();
            src.close();
            dst.close();
            //closes the file stream and reopens in the new openmode
            fh.close();
            fh.open(fileName, std::ofstream::trunc);
            app = false;
            return true;
        }
        else{std::cout<< "Already Truncating"<<endl;}
    }
    app = false;
    return false;
}

/**
 * Description:
 * these methods allow the user to directly handle the ouput stream from the Log class
**/
bool Log::close_fh(){try{fh.close();return true;}catch(...){std::cerr<< "file could not close." <<std::endl;return false;}return false;}
bool Log::flush_fh(){try{fh.flush();return true;}catch(...){std::cerr<< "file could not flush." <<std::endl;return false;}return false;}
bool Log::open_fh() {try{fh.open(fileName,std::ofstream::out | std::ofstream::app);return true;}catch(...){std::cerr<< "file could not open." <<std::endl;return false;}return false;}

/**
 * Description:
 * description: this method returns the state of the output stream
**/
bool Log::curr_state(){ return state = fh.is_open();}
