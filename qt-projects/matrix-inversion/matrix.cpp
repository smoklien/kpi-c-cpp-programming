#include "matrix.h"

int Matrix::complexity_ = 0;

int Matrix::getRows() const {
    return rows_;
}

int Matrix::getColumns() const {
    return columns_;
}

int Matrix::getComplexity() const {
    return complexity_;
}

void Matrix::resetCounter() {
    complexity_ = 0;
}

Matrix::Matrix(Matrix& other) 
    : matrix_(other.matrix_), rows_(other.rows_), columns_(other.columns_){}

Matrix::Matrix(QVector<QVector<double>> matrix) 
    :matrix_(matrix), columns_(matrix.size()), rows_(matrix.size()) {}

Matrix::Matrix(int size) 
    : matrix_(size, QVector<double>(size)), columns_(size), rows_(size) {}

Matrix::Matrix(int rows, int columns)
    : matrix_(rows, QVector<double>(columns)), rows_(rows), columns_(columns) {}

QString Matrix::toString() const {
    QString result;

    for (const auto& row : matrix_) {
        for (const auto& el : row) {
            result += QString::number(el, 'f', 4).rightJustified(10, ' ') + '|';
        }
        result += '\n';
    }

    return result;
}

QVector<double>& Matrix::operator[](int index) {
    return matrix_[index];
}

const QVector<double>& Matrix::operator[](int index) const {
    return matrix_[index];
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(rows_, other.columns_);
    
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.columns_; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < columns_; ++k) {
                result[i][j] += matrix_[i][k] * other[k][j];
                complexity_ ++;
            }
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rows_, columns_);
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            result[i][j] = matrix_[i][j] + other[i][j];
            complexity_++;
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows_, columns_);
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            result[i][j] = matrix_[i][j] - other[i][j];
            complexity_ ++;
        }
    }

    return result;
}

Matrix Matrix::operator-() const {
    Matrix result(rows_, columns_);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < columns_; ++j) {
            result[i][j] = -matrix_[i][j];
            complexity_++;
        }
    }
    
    return result;
}

QVector<double> Matrix::solveLU(Matrix& L, Matrix& U, QVector<double>& b) {
    int sizeOfL = L.getRows();

    QVector<double> y(sizeOfL, 0.0);  // Вектор для збереження проміжних результатів обчислення у
    QVector<double> x(sizeOfL, 0.0);  // Вектор для збереження розв'язку x

    // Обчислення вектору y шляхом прямого підстановлення
    for (int i = 0; i < sizeOfL; i++) {
        double sum = 0;
         for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
            complexity_++;
        }
        y[i] = (b[i] - sum) / L[i][i];
    }

    // Обчислення вектору x шляхом зворотного підстановлення
    for (int i = sizeOfL - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < sizeOfL; j++) {
            sum += U[i][j] * x[j];
            complexity_++;
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    return x;
}

void Matrix::LUdecompose(Matrix& L, Matrix& U, double& determinant) {
    int sizeOfMatrix = matrix_.size();
    determinant = 1.0;
    double tolerance = 1e-5;

    // Розкладання матриці на нижню (L) і верхню (U) трикутні матриці
    for (int i = 0; i < sizeOfMatrix; i++) {
        for (int k = i; k < sizeOfMatrix; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
                complexity_++;
            }
            U[i][k] = matrix_[i][k] - sum;
        }

        for (int k = i; k < sizeOfMatrix; k++) {
            // Елементи діагоналі нижньої матриці дорівнюють 1
            if (i == k) {
                L[i][i] = 1;
            }
            else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += (L[k][j] * U[j][i]);
                    complexity_++;
                }
                if (abs(U[i][i]) < tolerance) {
                    throw std::logic_error("Обраний вами метод не працює на даній матриці");
                }
                L[k][i] = (matrix_[k][i] - sum) / U[i][i];
            }
        }

        determinant *= U[i][i];
    }
}

Matrix Matrix::invertByLU() {
    int sizeOfMatrix = matrix_.size();

    Matrix L(sizeOfMatrix);  
    Matrix U(sizeOfMatrix); 
    double determinant;
    double tolerance = 1e-5;

    LUdecompose(L, U, determinant);

    if (abs(determinant) < tolerance) {
        throw std::logic_error("Обраний вами метод не працює на даній матриці");
    }

    Matrix inverse(sizeOfMatrix);  
    for (int i = 0; i < sizeOfMatrix; i++) {
        QVector<double> e(sizeOfMatrix, 0.0);
        e[i] = 1;
        // Розв'язуємо систему лінійних рівнянь для кожного стовпця оберненої матриці
        QVector<double> x = solveLU(L, U, e); 
        for (int j = 0; j < sizeOfMatrix; j++) {
            inverse[j][i] = x[j];
        }
    }

    return inverse;
}


Matrix Matrix::mergeBlocks(const Matrix& A, const  Matrix& B, const Matrix& C, const  Matrix& D) {
    int sizeOfA = A.getColumns();
    int nCols = sizeOfA + B.getColumns();
    int nRows = sizeOfA + C.getRows();

    Matrix result(nRows, nRows);

    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++) {
            // Злиття кліток матриці A, B, C і D у нову матрицю result

            // Якщо поточний рядок та стовпець знаходяться в межах розміру матриці A,
            // копіюємо відповідний елемент з матриці A
            if ((i < sizeOfA) && (j < sizeOfA)) {
                result[i][j] = A[i][j];
            }
            // Якщо поточний рядок знаходиться в межах розміру матриці A, а поточний стовпець
            // виходить за межі розміру матриці A, копіюємо відповідний елемент з матриці B
            else if (i < sizeOfA) {
                result[i][j] = B[i][j - sizeOfA];
            }
            // Якщо поточний стовпець знаходиться в межах розміру матриці A, а поточний рядок
            // виходить за межі розміру матриці A, копіюємо відповідний елемент з матриці C
            else if (j < sizeOfA) {
                result[i][j] = C[i - sizeOfA][j];
            }
            // Якщо ні рядок, ні стовпець не знаходяться в межах розміру матриці A, копіюємо
            // відповідний елемент з матриці D
            else {
                result[i][j] = D[i - sizeOfA][j - sizeOfA];
            }
            complexity_++;
        }
    }

    return result;
}

std::tuple<Matrix, Matrix, Matrix, Matrix> Matrix::divideIntoBlocks(const Matrix& inputMatrix) {
    int sizeOfMatrix = inputMatrix.getRows();
    int p = (sizeOfMatrix % 2 == 1) ? (sizeOfMatrix / 2 + 1) : (sizeOfMatrix / 2);

    Matrix A(p, p);
    Matrix B(p, sizeOfMatrix - p);
    Matrix C(sizeOfMatrix - p, p);
    Matrix D(sizeOfMatrix - p, sizeOfMatrix - p);

    for (int i = 0; i < sizeOfMatrix; ++i) {
        for (int j = 0; j < sizeOfMatrix; ++j) {
            // Розбиваємо вхідну матрицю на клітки A, B, C і D

            // Якщо поточний рядок і стовпець знаходяться в межах розміру клітки A,
            // копіюємо відповідний елемент у клітку A
            if (i < p && j < p) {
                A[i][j] = inputMatrix[i][j];
            }
            // Якщо поточний рядок знаходиться в межах розміру клітки A, а поточний стовпець
            // виходить за межі розміру клітки A, копіюємо відповідний елемент у клітку B
            else if (i < p) {
                B[i][j - p] = inputMatrix[i][j];
            }
            // Якщо поточний стовпець знаходиться в межах розміру клітки A, а поточний рядок
            // виходить за межі розміру клітки A, копіюємо відповідний елемент у клітку C
            else if (j < p) {
                C[i - p][j] = inputMatrix[i][j];
            }
            // Якщо ні рядок, ні стовпець не знаходяться в межах розміру клітки A, копіюємо
            // відповідний елемент у клітку D
            else {
                D[i - p][j - p] = inputMatrix[i][j];
            }
            complexity_++;
        }
    }


    return std::make_tuple(A, B, C, D);
}

Matrix Matrix::invertByBlock(Matrix& matrix) {
    int sizeOfMatrix = matrix.getColumns();
    double tolerance = 1e-5;

    // Обернена матриця 1х1
    if (sizeOfMatrix == 1) {
        double determinant = matrix[0][0];
        
        if (fabs(determinant) < tolerance) {
            throw std::logic_error("Обраний вами метод не працює на даній матриці");
        }

        matrix[0][0] = 1 / determinant;
    }
    // Обернена матриця 2х2
    else if (sizeOfMatrix == 2) {
        double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        if (fabs(determinant) < tolerance) {
            throw std::logic_error("Обраний вами метод не працює на даній матриці");
        }

        double temp = matrix[0][0];
        matrix[0][0] = matrix[1][1] / determinant;
        matrix[1][1] = temp / determinant;
        matrix[0][1] = -matrix[0][1] / determinant;
        matrix[1][0] = -matrix[1][0] / determinant;
    }
    else {
        // Розбиваємо вхідну матрицю на клітки A, B, C і D
        std::tuple<Matrix, Matrix, Matrix, Matrix> result = divideIntoBlocks(matrix);
        Matrix A = std::get<0>(result);
        Matrix B = std::get<1>(result);
        Matrix C = std::get<2>(result);
        Matrix D = std::get<3>(result);

        // Рекурсивно обертаємо клітку D
        D = invertByBlock(D);

        // Знаходимо першу клітку оберненої матриці
        Matrix firstBlock = A - B * D * C;

        firstBlock = invertByBlock(firstBlock);
        
        // Знаходимо всі інші клітки за допомогою першої 
        Matrix secondBlock = -firstBlock * B * D;
        Matrix thirdBlock = -D * C * firstBlock;
        Matrix fourthBlock = D + D * C * firstBlock * B * D;

        // Злиття кліток в обернену матрицю
        matrix = mergeBlocks(firstBlock, secondBlock, thirdBlock, fourthBlock);
    }
    // рахування глибини рекурсії
    complexity_++;

    return matrix;
}