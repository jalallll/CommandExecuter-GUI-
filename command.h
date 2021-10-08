#ifndef COMMAND_H
#define COMMAND_H

#include <boost/process.hpp>
#include <boost/process/io.hpp>
#include <iostream>
#include <string>

class Command{
    public:
        explicit Command();
        std::string getCommand();
        std::string getOutput();
        int getReturnCode();
        
        void execute(std::string command);



    private:
        void setCommand(std::string command);
        std::string command;
        std::string output;
        int returnCode;




    
};

#endif