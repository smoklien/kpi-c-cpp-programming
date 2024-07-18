#pragma once

#include <QDialog>
#include <QTableWidget>
#include "matrix.hpp"
#include <QStandardItemModel>
#include <QMessageBox>
#include <qfiledialog>

namespace Ui
{
    class MatrixInversion;
}

class MatrixInversion : public QDialog
{
    Q_OBJECT

public:
    MatrixInversion(QWidget *, bool, int, Matrix *);
    ~MatrixInversion();

private slots:
    void on_pushButtonSubmit_clicked();
    void on_pushButtonInfo_clicked();
    void on_pushButtonSave_clicked();

private:
    Ui::MatrixInversion *ui;
    bool method_;
    int size_;
    Matrix *inputMatrix_;
    Matrix *invertedMatrix_;
    QString info[2] = {"Метод розбиття на клітки є одним із багатьох способів обертання матриці. "
                       "Цей метод дозволяє ефективно обернути великі матриці, розбиваючи їх на менші блоки "
                       "та використовуючи аналітичну формулу для обертання.",
                       "Метод LU-розкладу (Lower-Upper decomposition) розбиває матрицю на добуток "
                       "нижньотрикутної (L) і верхньотрикутної (U) матриць. Цей розклад дозволяє ефективно "
                       "розв'язувати системи лінійних рівнянь, обертати матриці та обчислювати визначники. "
                       "Він є важливим інструментом у чисельному аналізі та лінійній алгебрі."};
    void matrixWidgetDisplay();
    void pushButtonsDisplay();
};
