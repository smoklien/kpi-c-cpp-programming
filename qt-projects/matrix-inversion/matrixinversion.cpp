#include "matrixinversion.hpp"
#include "ui_matrixinversion.h"

MatrixInversion::MatrixInversion(QWidget *parent, bool method, int size, Matrix *matrix)
    : QDialog(parent), ui(new Ui::MatrixInversion), method_(method), size_(size)
{
    inputMatrix_ = new Matrix(*matrix);
    invertedMatrix_ = new Matrix(inputMatrix_->getColumns());

    matrix->resetCounter();

    if (method)
        *invertedMatrix_ = matrix->invertByBlock(*matrix);
    else
        *invertedMatrix_ = matrix->invertByLU();

    this->setFixedSize(260 + size_ * 100, 160 + size_ * 30);
    this->setMaximumSize(700, 700);
    ui->setupUi(this);

    matrixWidgetDisplay();
    pushButtonsDisplay();
}

MatrixInversion::~MatrixInversion()
{
    delete invertedMatrix_;
    delete inputMatrix_;
    delete ui;
}

void MatrixInversion::on_pushButtonSubmit_clicked()
{
    this->close();
}

void MatrixInversion::on_pushButtonInfo_clicked()
{
    QMessageBox::information(this, "Інформація про метод", (method_ ? info[0] : info[1]) + "\nПрактична складність: " + QString::number(invertedMatrix_->getComplexity()));
}

void MatrixInversion::on_pushButtonSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Зберегти матрицю", "", "Text Files (*.txt)");

    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Помилка збереження", "Неможливо зберегти файл.");
        return;
    }

    QTextStream out(&file);
    out << "\n---> Вхідна матриця:\n\n";
    out << inputMatrix_->toString();
    out << "\n---> Обернена матриця:\n\n";
    out << invertedMatrix_->toString();
    file.close();

    QMessageBox::information(this, "Успіх", "Матриця успішно збережена.");
}

void MatrixInversion::matrixWidgetDisplay()
{
    ui->inputMatrixWidget->setRowCount(size_);
    ui->inputMatrixWidget->setColumnCount(size_);
    ui->invertedMatrixWidget->setRowCount(size_);
    ui->invertedMatrixWidget->setColumnCount(size_);

    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            QTableWidgetItem *invertedItem = new QTableWidgetItem(QString::number((*invertedMatrix_)[i][j]));
            invertedItem->setFlags(invertedItem->flags() & ~Qt::ItemIsEditable);
            ui->invertedMatrixWidget->setItem(i, j, invertedItem);

            QTableWidgetItem *inputItem = new QTableWidgetItem(QString::number((*inputMatrix_)[i][j]));
            inputItem->setFlags(inputItem->flags() & ~Qt::ItemIsEditable);
            ui->inputMatrixWidget->setItem(i, j, inputItem);
        }
    }
}

void MatrixInversion::pushButtonsDisplay()
{
    ui->buttonLayout->setContentsMargins(size_ * 40, 0, size_ * 40, 0);
    ui->buttonLayout->setSpacing(size_ * 5);
}
