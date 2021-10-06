#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QString>

namespace Ui {
  class MainWindow;
}
 
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

private:
  void createCommandBox();
  void createOutputBox();
  void createExitStatusBox();
  void createHistoryBox();
  void addCommand(std::string command, std::string status, std::string result);
  void handleButton();
  
  QGroupBox *commandBox;
  QGroupBox *outputBox;
  QGroupBox *statusBox;
  QGroupBox *historyBox;

  QVBoxLayout *outputLayout;
  QVBoxLayout *historyLayout;

  QLineEdit *commandInput;
  QPushButton *executeButton;

  std::string command;

  QLabel *status;
  QLabel *commandHistory[100];
  QLabel *outputHistory[100];

  QVBoxLayout *mainLayout;

};
#endif // MAINWINDOW_H