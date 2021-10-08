/*
Author: Jalal Qureshi

Description of file contents: This file defines the function prototypes and instance variables of the mainWindow class
                              
Date: 10/05/2021
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QString>
#include <QTextEdit>
#include <QListWidget>


#include "command.h"



namespace Ui {
  class MainWindow;
}
 
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void createCommandBox();
  void createOutputBox();
  void createExitStatusBox();
  void createHistoryBox();
  void addCommand(std::string command, std::string status, std::string result);
  void handleButton();
  void onItemClicked(QListWidgetItem *item);
  
  QGroupBox *commandBox;
  QGroupBox *outputBox;
  QGroupBox *statusBox;
  QGroupBox *historyBox;
  QVBoxLayout *outputLayout;
  QVBoxLayout *historyLayout;
  QHBoxLayout *statusLayout;
  QLineEdit *commandInput;
  QPushButton *executeButton;
  //std::string command;
  QLabel *statusLabel;
  QLabel *outputLabel;

  QVBoxLayout *mainLayout;
  QTextEdit *outputList;
  std::vector<Command> commandVector;
  QListWidget *commandHistory;



  int commandNum;

};
#endif // MAINWINDOW_H