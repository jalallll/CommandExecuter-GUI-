#include "mainwindow.h"
#include "command.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
 
  // make window
  QWidget *window = new QWidget();
  window->setMaximumSize(500,500);

 
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
  window->show();
  this->commandNum=0;
}

void MainWindow::handleButton()
{
  QString command = commandInput->text();
  string commandString = command.toStdString();
  // if command is empty or contains all spaces then prompt user
  if(commandString.length()==0||commandString.find_first_not_of(' ') == std::string::npos){
     string prompt = "Please Enter Valid Command";
     QString qPrompt = QString::fromStdString(prompt);
     outputList->setText(qPrompt);

  }
  else{
    
    Command cm(commandString);
    string output = cm.getOutput();
    int statusCode = cm.getReturnCode();
    QString status = QString::number(statusCode);
    statusLabel->setText(status);
    QString outputQstr = QString::fromStdString(output);

    outputList->setText(outputQstr);

    this->commandNum++;
    QString historyEntry = QString::number(this->commandNum);
    historyEntry.append(")  " + command + " | " + status + " | " + outputQstr +"\n");
    commandHistory->append(historyEntry);
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
  outputBox =new QGroupBox("Output");

  //box layout
  outputLayout = new QVBoxLayout(outputBox);

  outputList = new QTextEdit();
  outputList->setReadOnly(true);
  outputList->setLineWrapColumnOrWidth(50);
  outputList->setWordWrapMode(QTextOption::WordWrap	);

  outputLayout->addWidget(outputList);

}


void MainWindow::createExitStatusBox(){

  //make the box
  statusBox = new QGroupBox();

  //make parts of box
  QLabel *label = new QLabel("Exit Status: ");
  // box layout
  statusLayout = new QHBoxLayout;
  //add stuff to box layout
  statusLayout->addWidget(label);
  //set layout of box
  statusBox->setLayout(statusLayout);

  statusLabel = new QLabel(" ");
  statusLayout->addWidget(statusLabel);
}

void MainWindow::createHistoryBox(){

  //make the box
  historyBox = new QGroupBox("History: ");

  // box layout
  historyLayout = new QVBoxLayout;
  //set layout of box
  historyBox->setLayout(historyLayout);

  commandHistory = new QTextEdit();
  commandHistory->setReadOnly(true);
  commandHistory->setLineWrapColumnOrWidth(50);
  commandHistory->setWordWrapMode(QTextOption::WordWrap	);

  historyLayout->addWidget(commandHistory);
}


