/*
Author: Jalal Qureshi

Description of file contents: This file uses the boost library to execute system level commands
                              and return corresponding standard output and standard error

Date: 10/04/2021
*/

#include "command.h"

using namespace boost::process;

/*
Function name: Command

Description: Constructor for class Command
                              
Parameter descriptions: None

Return description: A Command object
*/

Command::Command(){
    // initialize global variables
    this->command = "";
    this->returnCode=0;
    this->output="";
}

/*
Function name: ~Command

Description: Deconstructor for class Command
                              
Parameter descriptions: None

Return description: None
*/

Command::~Command(){

}

/*
Function name: getCommand

Description: Getter method for command
                              
Parameter descriptions: None

Return description: Return a string storing the command
*/

std::string Command::getCommand(){
    return this->command;
}

/*
Function name: getCommand

Description: Getter method for command
                              
Parameter descriptions: None

Return description: Return a string storing the command
*/

std::string Command::getOutput(){
    return this->output;
}

/*
Function name: getReturnCode

Description: Getter method for return code
                              
Parameter descriptions: None

Return description: Return an int storing the return code
*/

int Command::getReturnCode(){
    return this->returnCode;
}

/*
Function name: execute

Description: Execute given command by creating a stream for the child process and then setting the value of the output and return code instance variables
                              
Parameter descriptions: A string containing the command to be executed

Return description: void
*/

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

/*
Function name: setCommand

Description: Setter method for the instance variable command
                              
Parameter descriptions: A string containing the command

Return description: void
*/

void Command::setCommand(std::string command){
    this->command = command;
}





