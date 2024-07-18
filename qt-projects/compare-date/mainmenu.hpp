#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainmenu.h"
#include "date.hpp"

#include <QMessageBox>

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_submitButton_clicked();

private:
    Ui::MainMenuClass *ui;
    Date *firstDate_;
    Date *secondDate_;
    QString *firstDateString_;
    QString *secondDateString_;
    const int NUMBER_OF_DATES = 2;

    void compareDate();
};
