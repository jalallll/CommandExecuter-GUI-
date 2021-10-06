QT += core widgets gui
TARGET = CommandGUI
TEMPLATE = app 
SOURCES += main.cpp mainwindow.cpp command.cpp
HEADERS += mainwindow.h command.h
LIBS += -lboost_thread -lpthread 
