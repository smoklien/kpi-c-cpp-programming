#pragma once

#include <QVector>
#include <qtextstream>
#include <tuple>

class Matrix
{
private:
    QVector<QVector<double>> matrix_;
    int rows_;
    int columns_;
    static int complexity_;

public:
    Matrix(Matrix &);
    Matrix(QVector<QVector<double>>);
    Matrix(int);
    Matrix(int, int);

    int getColumns() const;
    int getRows() const;
    int getComplexity() const;
    void resetCounter();

    QString toString() const;

    void LUdecompose(Matrix &, Matrix &, double &);
    QVector<double> solveLU(Matrix &, Matrix &, QVector<double> &);
    Matrix invertByLU();

    Matrix mergeBlocks(const Matrix &A, const Matrix &B, const Matrix &C, const Matrix &D);
    std::tuple<Matrix, Matrix, Matrix, Matrix> divideIntoBlocks(const Matrix &);
    Matrix invertByBlock(Matrix &);

    Matrix operator*(const Matrix &) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator-() const;

    QVector<double> &operator[](int index);
    const QVector<double> &operator[](int index) const;
};
