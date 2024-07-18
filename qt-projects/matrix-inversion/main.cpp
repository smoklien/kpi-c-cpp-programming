#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow menu;
    menu.show();
    return a.exec();
}