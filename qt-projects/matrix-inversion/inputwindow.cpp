#include "inputwindow.hpp"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QWidget *parent, bool method, int size)
    : QDialog(parent), ui(new Ui::InputWindow), method_(method), size_(size)
{
    inputMatrix_ = new Matrix(size_);

    this->setFixedSize(130 + size_ * 55, 150 + size_ * 35);
    ui->setupUi(this);

    matrixWidgetDisplay();
    pushButtonsDisplay();
}

InputWindow::~InputWindow()
{
    delete inputMatrix_;
    delete ui;
}

void InputWindow::on_pushButtonSubmit_clicked()
{
    for (int row = 0; row < size_; row++)
    {
        for (int column = 0; column < size_; column++)
        {
            QTableWidgetItem *item = ui->inputMatrixWidget->item(row, column);

            bool isValueNumber = false;
            double value = item ? item->text().toDouble(&isValueNumber) : 0.0;

            if (isValueNumber)
            {
                QString valueString = item->text();
                size_t decimalPos = valueString.indexOf('.');
                int precision = valueString.length() - decimalPos - 1;

                if (abs(value) > MAX_VALUE)
                {
                    QMessageBox::critical(this, "Некоректний ввід", "Значення надто велике.");
                    return;
                }
                else if (precision > MAX_PRECISION)
                {
                    QMessageBox::critical(this, "Некоректний ввід", "Надто велика кількість знаків після коми (> 5).");
                    return;
                }
                (*inputMatrix_)[row][column] = value;
            }
            else
            {
                QMessageBox::critical(this, "Некоректний ввід", "Було введено некоректне значення. Вводити можливо лише цифри.");
                return;
            }
        }
    }
    try
    {
        MatrixInversion window(this, method_, size_, inputMatrix_);
        window.setWindowTitle("Обернення матриць");
        window.setModal(true);
        window.exec();
    }
    catch (const std::logic_error &e)
    {
        QMessageBox::critical(this, "Помилка обрахувань", e.what());
        return;
    }
}

void InputWindow::on_pushButtonClear_clicked()
{
    ui->inputMatrixWidget->clear();
}

void InputWindow::matrixWidgetDisplay()
{
    ui->inputMatrixWidget->setRowCount(size_);
    ui->inputMatrixWidget->setColumnCount(size_);

    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            QTableWidgetItem *inputItem = new QTableWidgetItem(QString::number((*inputMatrix_)[i][j]));
            ui->inputMatrixWidget->setItem(i, j, inputItem);
        }
    }
}

void InputWindow::pushButtonsDisplay()
{
    ui->buttonLayout->setContentsMargins(size_ * 20, 0, size_ * 20, 0);
    ui->buttonLayout->setSpacing(4 + size_ * 2);
}
