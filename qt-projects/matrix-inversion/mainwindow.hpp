#pragma once

#include <QMainWindow>
#include "matrix.hpp"
#include "matrixinversion.hpp"
#include "inputwindow.hpp"
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCreate_clicked();

private:
    Ui::MainWindow *ui;
    Matrix *generateRandomMatrix(int);
};
