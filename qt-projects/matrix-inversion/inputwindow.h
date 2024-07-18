#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include "matrixinversion.h"
#include "matrix.h"

namespace Ui {
    class InputWindow;
}

class InputWindow : public QDialog
{
    Q_OBJECT

public:
    InputWindow(QWidget*, bool, int);
    ~InputWindow();

private slots:
    void on_pushButtonSubmit_clicked(); 
    void on_pushButtonClear_clicked(); 

private:
    Ui::InputWindow* ui;
    Matrix *inputMatrix_;
    bool method_;
    int size_;

    const int MAX_PRECISION = 4;
    const int MAX_VALUE = 1e4;

    void matrixWidgetDisplay();
    void pushButtonsDisplay();
};