#ifndef CONFIG_H
#define CONFIG_H
/*
 * This class is specifically built to facilitate the storage of
 * general program information that can be used in setting of
 * default values and/or pre-recorded program information.
 *
 * This class is designed as a state machine with nine states:
 *
 ***Constructor : constructs class
 ***File Checking : checking whether configuration file exists
 ***Create file : creating configuration file if it doesn't exist
 ***Read file : reading from the configuration file
 ***Set Defaults : setting default program values
 ***Configuration : configuring program values using configuration
 ***  file data
 ***Program running : listening for read/write requests as program runs
 ***Write file : writing to the configuration file
 ***Destructor : destroys class on exit
 *
 * After class is constructed, the class checks for a configuration
 * file. If present, the file is read and relevant program values
 * are set. If there is no configuration file, default values are
 * set. The program then enters the in-program reads/writes state,
 * where read and write requests are listened for. Respective reads
 * and writes are granted. When the program is ending, the class
 * checks for a configuration file. If found, the program-end values
 * are recorded in the file, but if not, a configuration file is
 * created and values recorded. The class is then destroyed and the
 * program is closed
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstdio>
#include <unistd.h>
#include <pwd.h>
#include "baseclass.h"

using namespace std;

class Config : public baseclass
{
public:
    Config();  // default constructor
    Config(Config &obj);
    void operator= (Config &obj);
    int someData;

    int check_for_file(string filePath);
    int create_file(std::string filePath);
    void print_map();
    string change_file_path(std::string filePath);
    void initialize_files();
    string get_config_path();
    void set_map_defaults();
    void change_file_name(string pathToFile, string prevName, string newName);
    void update_config_file(string filePath);
    int write_to_file(std::string filePath, std::string data);
    std::map <string,int> read_config(std::string filePath);
    ~Config(); // destructor

    map <string,int> container;
    bool filePresent;
    string state;
    // overloaded handler operator
    //config& operator<<(const std::string str);

private:


};

#endif // CONFIG_H
