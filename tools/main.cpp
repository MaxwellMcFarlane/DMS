#include <iostream>
#include "log.h"
#include "config.h"
#include "macros.h"

using namespace std;

// Object of type Log globally instantiated.
Log err_log("test.txt");
Config conf; //Create a configuration class

/**
 * @brief main method runs all tests to
 * function accuracy of the log class and
 * the config class.
 * @return int
 */

int main()
{

    //Print map values
    conf.print_map();

    //These variables help verify the methods by inspecting the test.txt file
    std::string v0;
    ifstream tst_tool;
    tst_tool.open("test.txt",std::ifstream::in);

    /*Log File Tests Start*/
    //@test1: appends previous data ***
    getline(tst_tool, v0);
    if(v0.compare("Hey, I'm Max!") == 0||v0.compare("") == 0){std::cout << "\n@test1: correct\n";}
    else{std::cout << "\n@test1: incorrect\n";}

    //@test2: truncates previous data
    err_log.trunc_file();
    tst_tool.close();
    tst_tool.open("test.txt",std::ifstream::in);
    getline(tst_tool, v0);
    if(v0.compare("") == 0){std::cout << "@test2: correct\n";}
    else{std::cout << "@test2: incorrect\n";}

    //@test3: writes all data types to log and chains statements
    double rf = 20;
    long rg = 30;
    err_log << "test" << 3 << 4.98 << rf << rg;
    tst_tool.close();
    tst_tool.open("test.txt",std::ifstream::in);
    getline(tst_tool, v0);
    if(v0.compare("test34.982030") == 0){std::cout << "@test3: correct\n";}
    else{std::cout << "@test3: incorrect\n";}

    //@test4: switches from truncate to append
    if(err_log.app_file()){std::cout << "@test4: correct\n";}
    else{std::cout << "@test4: incorrect\n";}

    //@test5: switches from append to truncate
    if(err_log.trunc_file()){std::cout << "@test5: correct\n";}
    else{std::cout << "@test5: incorrect\n";}

    //@test6: opens
    if(err_log.open_fh()){std::cout << "@test6: correct\n";}
    else{std::cout << "@test6: incorrect\n";}

    //@test7: flushes
    if(err_log.flush_fh()){std::cout << "@test7: correct\n";}
    else{std::cout << "@test7: incorrect\n";}

    //@test8: closes
    if(err_log.flush_fh()){std::cout << "@test8: correct\n";}
    else{std::cout << "@test8: incorrect\n";}

    //@test9: returns current state
    err_log.open_fh();
    if(err_log.curr_state()){std::cout << "@test9a: correct\n";}
    else{std::cout << "@test9a: incorrect\n";}
    err_log.close_fh();
    if(!err_log.curr_state()){std::cout << "@test9b: correct\n";}
    else{std::cout << "@test9b: incorrect\n";}

    //@test10: doesn't save data to switch from tuncate to truncate
    err_log.trunc_file();
    if(!err_log.trunc_file()){std::cout << "@test10: correct\n";}
    else{std::cout << "@test10: incorrect\n";}

    //@test11: doesn't save data to switch from append to append
    err_log.app_file();
    if(!err_log.app_file()){std::cout << "@test11: correct\n";}
    else{std::cout << "@test11: incorrect\n";}

    //log info to predict @test1 results
    tst_tool.close();
    err_log.open_fh();
    err_log << "Hey, I'm Max!";
    err_log.flush_fh();
      /*Log File Tests End*/
    return 0;
}
