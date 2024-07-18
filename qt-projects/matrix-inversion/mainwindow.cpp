#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonCreate_clicked() {
    bool isMatrixRandom = ui->rbGenerateInput->isChecked();
    bool method = ui->rbFirstMethod->isChecked();
    int sizeOfMatrix = ui->spinBox->value();

    if (isMatrixRandom) {
        Matrix* generatedMatrix = generateRandomMatrix(sizeOfMatrix);
        MatrixInversion window(this, method, sizeOfMatrix, generatedMatrix);
        window.setWindowTitle("Результати");
        window.setModal(true);
        window.exec();
        delete generatedMatrix;
    }
    else {
        InputWindow window(this, method, sizeOfMatrix);
        window.setWindowTitle("Створення матриці");
        window.setModal(true);
        window.exec();
    }
}

Matrix* MainWindow::generateRandomMatrix(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Діапазон випадкових чисел від -10000.000 до 10000.000

    std::uniform_real_distribution<double> distribution(-10000.0, 10000.0);

    Matrix* randomMatrix = new Matrix(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double randomValue = distribution(gen);
            randomValue = round(randomValue * 10000.0) / 10000.0;  // Ліміт до чотирьох знаків після коми
            (*randomMatrix)[i][j] = randomValue;
        }
    }
    return randomMatrix;
}