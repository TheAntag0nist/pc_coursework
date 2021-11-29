#include <iostream>
#include <fstream>
#include <iomanip>

// for calculate time
#include <zconf.h>
#include <chrono>
#include <map>

// global data
#include "command.h"
#define MODULE_START "sudo insmod ../driver_main.ko off_on_flag=1"
#define MODULE_STOP "sudo rmmod driver_main"

std::string command = "";
std::string dir_1 = "";
std::string dir_2 = "";

// main func
int main(void){
    Command my_cmd;
    // start
    std::cout << "[+]:> Start program;" << std::endl;
    my_cmd.set_version("0.0.1v");

    uid_t uid = getuid();
    if (uid != 0) {
        std::cout << "[FTL]:> it's sudo programm;";
        return 1;
    }

    // begin -> main code
    // brain storm code
    // joke)))
    while (!my_cmd.is_active())
    {
        // try only in first version
        // just for upgrading using exceptions
        try{
            cout << "move_file:> ";
            cin >> command;
            // no cache
            if(command == "-nocache"){
                system(MODULE_START);
                continue;
            }
            // on cache
            if(command == "-cache"){
                system(MODULE_STOP);
                continue;
            }
            // execute command
            my_cmd.execute(command);
            // end   -> main code
        }catch(std::exception& ex){
            std::cout << "move_file:> exception -> " << ex.what() << std::endl; 
        }
    }
    // stop
    std::cout << "[INF]:> Stop program" << std::endl;

    return 0;
}