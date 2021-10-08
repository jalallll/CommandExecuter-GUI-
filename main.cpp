/*
Author: Jalal Qureshi

Description of file contents: This file contains the main method used to invoke the constructor in the mainWindow file and display the GUI
                              
Date: 10/05/2021
*/
#include "mainwindow.h"

/*
Function name: main

Description: Main method to execute program
                              
Parameter descriptions: Take an array of arguments from command

Return description: Return executable for QApplication
*/
int main(int argc, char *argv[]) 
{
  QApplication app(argc, argv);
  
  MainWindow mw;
  mw.show();

  return app.exec();
}