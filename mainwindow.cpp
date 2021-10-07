#include "mainwindow.h"
#include "command.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  QScrollArea *scrollArea = new QScrollArea();
  scrollArea->resize(400,400);
  scrollArea->setWidgetResizable(true);
  // make window
  QWidget *window = new QWidget(scrollArea);
  window->resize(300,300);
  scrollArea->setWidget(window);

 
  //main layout
  mainLayout = new QVBoxLayout(window);
  
  createCommandBox();
  createOutputBox();
  createExitStatusBox();
  createHistoryBox();

  //add box to main layout
  mainLayout->addWidget(commandBox);
  mainLayout->addWidget(outputBox);
  mainLayout->addWidget(statusBox);
  mainLayout->addWidget(historyBox);

  connect(executeButton, &QPushButton::released, this, &MainWindow::handleButton);
  scrollArea->show();
  this->commandNum=0;
}

void MainWindow::handleButton()
{
  QString command = commandInput->text();
  string commandString = command.toStdString();
  // if command is empty or contains all spaces then prompt user
  if(commandString.length()==0||commandString.find_first_not_of(' ') == std::string::npos){
     string status = "Do not leave command input empty!";
     QString qstr = QString::fromStdString(status);
     this->statusLabel->setText(qstr);

  }
  else{
    
    
    Command cm(commandString);
    string output = cm.getOutput();
    int statusCode = cm.getReturnCode();
    QString status = QString::number(statusCode);
    statusLabel->setText(status);
    QString qstr = QString::fromStdString(output);

    QLabel *outLabel = new QLabel(qstr);
    outputLayout->addWidget(outLabel);

    this->commandNum++;
    QString historyEntry = QString::number(this->commandNum);
    historyEntry.append(")  " + command + " | " + status + " | " + qstr);
    QLabel *label = new QLabel(historyEntry);

    historyLayout->addWidget(label);
  }
  
  


  


}

void MainWindow::createCommandBox()
{

//make the box
  commandBox = new QGroupBox(tr("Enter A Command"));


  //make parts of box
  QLabel *label = new QLabel("Command: ");
  commandInput = new QLineEdit();
  executeButton = new QPushButton("Execute");
  // box layout
  QHBoxLayout *layout = new QHBoxLayout;
  //add stuff to box layout
  layout->addWidget(label);
  layout->addWidget(commandInput);
  layout->addWidget(executeButton);
  //set layout of box
  commandBox->setLayout(layout);

}

void MainWindow::createOutputBox(){
  
  //make the box
  outputBox = new QGroupBox(tr("Output"));

  // box layout
  outputLayout = new QVBoxLayout;

  //set layout of box
  outputBox->setLayout(outputLayout);

 

}


void MainWindow::createExitStatusBox(){

  //make the box
  statusBox = new QGroupBox(tr("Status: "));

  //make parts of box
  QLabel *label = new QLabel("Exit Status: ");
  // box layout
  statusLayout = new QHBoxLayout;
  //add stuff to box layout
  statusLayout->addWidget(label);
  //set layout of box
  statusBox->setLayout(statusLayout);

  statusLabel = new QLabel("NULL");
  statusLayout->addWidget(statusLabel);
}

void MainWindow::createHistoryBox(){

  //make the box
  historyBox = new QGroupBox(tr("History: "));

  // box layout
  historyLayout = new QVBoxLayout;
  //set layout of box
  historyBox->setLayout(historyLayout);

}


