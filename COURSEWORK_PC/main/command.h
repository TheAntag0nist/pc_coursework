#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <string>
#include <map>

using namespace std;

class Command;
typedef void (Command::*func)(string);

class Command{
private:
    map<string, func> functions;
    static bool close_prog;

    string filename;
    string new_path;

    string version_str;
    string cmd_command;

    void version(string str = "");
    void help(string str = "");
    void close(string str = "");

    void move_file(string file);
    void command_line_exec(string str);

public:
    Command();
    ~Command();

    void set_path(string path);
    void set_filename(string filename);
    void set_version(string vr);
    void set_cmd_comm(string str);

    bool is_active();
    void execute(string command);

};