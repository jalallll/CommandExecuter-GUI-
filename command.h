#ifndef COMMAND_H
#define COMMAND_H

#include <boost/process.hpp>
#include <boost/process/io.hpp>
#include <iostream>
#include <string>

class Command{
    public:
        explicit Command(std::string command);
        std::string getCommand();
        std::string getOutput();
        int getReturnCode();
        void setCommand(std::string command);


    private:
        std::string command;
        std::string output;
        int returnCode;
        void execute();



    
};

#endif