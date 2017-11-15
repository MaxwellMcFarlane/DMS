#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>
#include "baseclass.h"

using namespace std;
/**
 * @author: Maxwell McFarlane
 * @version: 1.0
 *<p>
 * Description: This class logs information that the user wants to catalog.
 * The user can either truncate the file specified or append to the specified file.
 * In addition, from the log the user can manipulate the main file stream.
 * <p>
**/

class Log : public baseclass
{
public:

    Log(); //default constructor (Log will be stored in default.txt)
    Log(Log &obj);
    void operator= (Log &obj);

    Log(std::string fileName);  // fileName constructor
    ~Log(); // destructor

    // overloaded handler operator
    Log& operator<<(const std::string str);
    Log& operator<<(const int);
    Log& operator<<(const float);
    Log& operator<<(const double);
    Log& operator<<(const long);

    // ouput stream manipulators
    bool open_fh();
    bool close_fh();
    bool flush_fh();

    //write options (clear or append)
    bool trunc_file();
    bool app_file();

    bool curr_state();//state of the output stream

private:

    std::ofstream fh; // The file handler.
    std::string fileName = "default.txt"; //tracks the fileName
    bool state = false;  // file_open = true, file_closed = false;
    bool app = true; //determines if the file handler is truncating or appending
    int some_data = 0;
};

#endif // LOG_H
