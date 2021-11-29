#include "command.h"

bool Command::close_prog = false;

Command::Command(){
    filename = "";
    new_path = "";
    version_str = "";
    cmd_command = "";

    functions["-version"] = (func)(&Command::version);
    functions["-v"] = (func)(&Command::version);

    functions["-help"] = (func)(&Command::help);
    functions["-h"] = (func)(&Command::help);

    functions["-close"] = (func)(&Command::close);
    functions["-c"] = (func)(&Command::close);

    functions["-set_version"] = (func)(&Command::set_version);
    functions["-set_vr"] = (func)(&Command::set_version);

    functions["-set_path"] = (func)(&Command::set_path);
    functions["-set_file"] = (func)(&Command::set_filename);

    functions["-move_file"] = (func)(&Command::move_file);
}

Command::~Command(){
    cout << "[INF]:> ~Command;" << endl;
}

void Command::help(string str){
    cout << "\t-help | -h - display that screen" << endl
         << "\t-version | -v - display version" << endl
         << "\t-close | -c - close programm" << endl
         << "\t-cmd - execute cmd commands" << endl
         << "\t-set_path - set new file path" << endl
         << "\t-set_file - set file for move" << endl
         << "\t-move_file - move file from one dir to another" << endl;
}

void Command::version(string str){
    cout << ("version: " + version_str) << endl;
}

void Command::close(string str){
    if(str != "")
        cout << str << endl;
    close_prog = true;
}

void command_line_exec(string str){
    // maybe will be upgraded in the future
}

void Command::set_path(string path){
    cout << "[INF]:> path = ";

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    getline(cin, path, '\n');
    new_path = path;
}
void Command::set_filename(string filename){
    cout << "[INF]:> filename = ";

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    getline(cin, filename, '\n');
    this->filename = filename;
}

void Command::set_version(string vr){
    if(vr == ""){
        cout << "[INF]:> version = ";
        getline(cin, vr, '\n');
    }

    version_str = vr;
}

void Command::set_cmd_comm(string str){
    cmd_command = str;
}

bool Command::is_active(){
    return close_prog;
}

void Command::execute(string command){
    // execute cmd commands
    /*
    if(command == "-cmd"){
        this->command_line_exec(cmd_command);
        return;
    }
    */

    // execute command
    if(functions.find(command) != functions.end()){
        func fn = functions[command];
        (this->*fn)("");
    }else
        cout << "[ERR]:> bad command;" << endl;
}

void Command::move_file(string str){
    cout << "[INF]:> move file process;" << endl;

    auto start_time = chrono::steady_clock::now();

    if(filename == ""){
        cout << "[ERR]:> error -> empty data;";
        return;
    }

    // move file
    ifstream ifs(filename, ios::in | ios::binary);
    ofstream ofs(new_path + "/" + filename, ios::out | ios::binary);
    ofs << ifs.rdbuf();
    remove(filename.c_str()); 

    auto end_time = chrono::steady_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);    
    std::cout << elapsed_ns.count() << " ns\n";
}