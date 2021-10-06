#include "command.h"


using namespace boost::process;

Command::Command(std::string command){
    setCommand(command);
    execute();
}

std::string Command::getCommand(){
    return this->command;
}

std::string Command::getOutput(){
    return this->output;
}

int Command::getReturnCode(){
    return this->returnCode;
}

void Command::setCommand(std::string command){
    this->command = command;
}

void Command::execute(){
    ipstream pipe_stream;
    std::string command = this->command;
    child c(command, std_out > pipe_stream);

    std::string line;

    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()){
        this->output = line;
        std::cerr << line << std::endl;

    }

    c.wait();
}


