#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
 
  // base class of all UI objects
  QWidget *window = new QWidget();
  // set max height to prevent resizing beyond this
  window->setMaximumSize(500,500);

  //main layout/base layout
  mainLayout = new QVBoxLayout(window);
  
  // execute helper functions to create 4 group boxes
  createCommandBox();
  createOutputBox();
  createExitStatusBox();
  createHistoryBox();

  //add each group box to the main layout
  mainLayout->addWidget(commandBox);
  mainLayout->addWidget(outputBox);
  mainLayout->addWidget(statusBox);
  mainLayout->addWidget(historyBox);

  // set up the signals and slots
  // when push button is released, a signal is sent to the slot handleButton which executes function
  connect(executeButton, &QPushButton::released, this, &MainWindow::handleButton);
  // when item in list is clicked, a signal is sent to the slot onItemClicked 
  connect(commandHistory, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);

  // show the base widget
  window->show();
}

void MainWindow::onItemClicked(QListWidgetItem *item)
{
  // get the row number of item currently selected from the commandHistory list
  // the row number starts at 0 and corresponds to the indices in the commandVector array
  int index = commandHistory->currentRow();

  // obtain the output of the command object at the specified index of the command vector array
  // convert the output from string to QString and replace the contents in the output box
  outputList->setText(QString::fromStdString(commandVector.at(index).getOutput()));

  // obtain the return code from the command vector at the specified index, convert it to QString, 
  // display the return code in the status box
  statusLabel->setText(QString::number(commandVector.at(index).getReturnCode()));
}

void MainWindow::handleButton()
{
  // get QString and string version of the input in the commandInput
  QString commandQstr = commandInput->text();
  string commandString = commandQstr.toStdString();

  // if command is empty or contains all spaces then prompt user
  if(commandString.length()==0||commandString.find_first_not_of(' ') == std::string::npos){
     string prompt = "Please Enter Valid Command";

     // convert the string prompt into QString so it can replace text of outputList
     QString qPrompt = QString::fromStdString(prompt);
     outputList->setText(qPrompt);

  }
  // if command inputted is not empty or contains characters other than spaces
  else{
    // instantiate command object with string containing the inputted command 
    Command commandObj;

    // execute the command
    commandObj.execute(commandString);

    // a vector storing command objects, add the command object just created into the back of the vector
    this->commandVector.push_back(commandObj);
    
    // from the vector storing command objects, 
    // obtain the return code and output corresponding to the command object of the command we just executed
    QString statusQstr = QString::number(commandVector.back().getReturnCode());
    QString outputQstr = QString::fromStdString(commandVector.back().getOutput());

    // set the text of the return code label with the return code we just obtained from executing the command
    statusLabel->setText(statusQstr);

    // set the text of the output list with the output we just obtained from executing the command
    outputList->setText(outputQstr);


    // Creating an entry that will be added to the command history list
    // get the size/number of elements in the vector storing command objects (will be used for numbering the entries)
    QString historyEntry = QString::number(commandVector.size());
    // append the entry number with the command executed and the return code
    historyEntry.append(")  " + commandQstr + "\t( " + statusQstr + " )\n");

    // add the entry to the command history list
    commandHistory->addItem(historyEntry);
  }
  
  


  


}

void MainWindow::createCommandBox()
{
  // A groupbox to contain and display the GUI widgets needed to enter and execute commands
  //initialize the group box which will contain the input area to enter the command and a button to execute the command
  commandBox = new QGroupBox(tr("Enter A Command"));

  //Display a label appearing to the left of the input area (where the command can be inputted)
  QLabel *label = new QLabel("Command: ");

  // Display an input area where user can input the command as text
  commandInput = new QLineEdit();

  // the button which the user clicks to execute the command
  executeButton = new QPushButton("Execute");

  // Initialize the layout of the commandBox groupbox 
  // The layout will horizontally display widgets in the groupbox
  QHBoxLayout *layout = new QHBoxLayout;

  // Set the layout initialized above as the layout of the commandBox groupbox
  commandBox->setLayout(layout);

  // Adding the widgets to the layout of the groupbox
  //Add the label, the command input aream, and the button into the layout of the groupbox
  layout->addWidget(label);
  layout->addWidget(commandInput);
  layout->addWidget(executeButton);



}

void MainWindow::createOutputBox(){
  
  // Initialize the group box which will display the output of the executed command
  outputBox =new QGroupBox("Output");

  // Initialize and set the layout of the groupbox
  // The layout display widgets in the groupbox vertically
  outputLayout = new QVBoxLayout(outputBox);

  // A QTextEdit widget, display the output received after executing a command
  outputList = new QTextEdit();
  // Set the QTextEdit widget to read only mode so users can't type into it
  outputList->setReadOnly(true);

  // After 50 pixels from the left of the QTextEdit widget, display the remaining output onto next line
  outputList->setLineWrapColumnOrWidth(50);
  
  // If long text does not fit on the line, put the next word on the next line, split the line at whitespace
  outputList->setWordWrapMode(QTextOption::WordWrap	);

  // Add the widget that will display the output of the command into the layout of the groupbox
  outputLayout->addWidget(outputList);

}


void MainWindow::createExitStatusBox(){

  // Initialize the group box which will contain the widgets needed to display the return code
  statusBox = new QGroupBox();

  // A label widget displayed to the right of the return code
  QLabel *label = new QLabel("Exit Status: ");

  // The layout of the group box widget, widgets in the groupbox displayed horizontally 
  statusLayout = new QHBoxLayout;

  // set the layout of the groupbox
  statusBox->setLayout(statusLayout);

  // Add the label widget to the group box layout
  statusLayout->addWidget(label);

  // Initialize and add an empty label to the layout
  // When an event is triggered and the return code is received, the label will be modified to display the return code
  statusLabel = new QLabel(" ");
  statusLayout->addWidget(statusLabel);
}

void MainWindow::createHistoryBox(){

  // Initialize the QGroupBox widget that will contain widgets displaying the history of the commands executed
  historyBox = new QGroupBox("History: ");

  // The layout of the QGroupBox widget, widgets will be displayed vertically
  historyLayout = new QVBoxLayout;
  
  // Set the layout of box
  historyBox->setLayout(historyLayout);

  // Initialize a QListWidget that will store the details of the commands executed
  commandHistory = new QListWidget();
  
  // Add the QlistWidget to the layout of the QGroupBox
  historyLayout->addWidget(commandHistory);
}


