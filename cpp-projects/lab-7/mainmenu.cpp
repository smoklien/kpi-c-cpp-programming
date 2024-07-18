#include "mainmenu.hpp"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainMenuClass)
{
    ui->setupUi(this);
    this->setFixedSize(320, 240);

    firstDateString_ = new QString();
    secondDateString_ = new QString();

    firstDate_ = nullptr;
    secondDate_ = nullptr;
}

MainMenu::~MainMenu()
{
    delete firstDateString_;
    delete secondDateString_;
    delete firstDate_;
    delete secondDate_;
    delete ui;
}

void MainMenu::on_submitButton_clicked()
{
    *firstDateString_ = ui->lineEdit_1->text();
    *secondDateString_ = ui->lineEdit_2->text();

    try
    {

        firstDate_ = new Date(firstDateString_);
        secondDate_ = new Date(secondDateString_);
    }
    catch (const Date::IncorrectDate &e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    catch (const Date::InvalidDateFormat &e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    compareDate();
}

void MainMenu::compareDate()
{

    if (*firstDate_ < *secondDate_)
    {
        QMessageBox::information(this, "Results", "First date is older: " + firstDate_->toString());
    }
    else if (*firstDate_ > *secondDate_)
    {
        QMessageBox::information(this, "Results", "Second date is older: " + secondDate_->toString());
    }
    else
    {
        QMessageBox::information(this, "Results", "Dates are equal");
    }
}
