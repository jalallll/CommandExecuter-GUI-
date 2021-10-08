#include "command.h"

using namespace boost::process;


Command::Command(){
    // initialize global variables
    this->command = "";
    this->returnCode=0;
    this->output="";
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



void Command::execute(std::string command){
    try{
        // create stream for child process
        ipstream pipe_stream;
        // set the command inputted
        setCommand(command);
        // create child process that executes the command and sends standard output and standard error into stream 
        child c(command, (std_out & std_err) > pipe_stream);

        // temporary variable to store each line read from input stream
        std::string line;

        // read each line from the stream and store it into temporary variable
        while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()){
            
            // concatenate each line read from the stream
            this->output += line + " ";
            std::cerr << line << std::endl;

        }
        // wait for child process to finish
        c.wait();
        // get return code from child process
        this->returnCode = c.exit_code();
    // Catch all possible exceptions thrown, if exception is thrown then set return code to -1
    } catch(...){
        this->returnCode=-1; 
    }
  
}


