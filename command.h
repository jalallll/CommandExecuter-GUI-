/*
Author: Jalal Qureshi

Description of file contents: This file defines the function prototypes and instance variables of the command class
                              
Date: 10/05/2021
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <boost/process.hpp>
#include <boost/process/io.hpp>


class Command{
    public:
        explicit Command();
        ~Command();
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