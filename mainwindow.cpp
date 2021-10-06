#include "mainwindow.h"
#include "command.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->resize(250,250);
  scrollArea->setWidgetResizable(true);
  // make window
  QWidget *window = new QWidget(scrollArea);
  window->resize(200,200);
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
}

void MainWindow::handleButton()
{
  // change the text
  //executeButton->setText("Example");
  QString command = commandInput->text();
  QLabel *label = new QLabel(command);
  historyLayout->addWidget(label);
  string commandString = command.toStdString();
  Command cm(commandString);
  string output = cm.getOutput();
  //output = "jj";
  QString qstr = QString::fromStdString(output);

  QLabel *outLabel = new QLabel(qstr);
  outputLayout->addWidget(outLabel);

  
 
  
  // cm.setCommand("hi");
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
  status = new QLabel("Null");
  // box layout
  QHBoxLayout *layout = new QHBoxLayout;
  //add stuff to box layout
  layout->addWidget(label);
  layout->addWidget(status);
  //set layout of box
  statusBox->setLayout(layout);
}

void MainWindow::createHistoryBox(){
  //make the box
  historyBox = new QGroupBox(tr("History: "));
  // box layout
  historyLayout = new QVBoxLayout;
  //set layout of box
  historyBox->setLayout(historyLayout);


}


