#include <qstring.h>
#include <QRegularExpression>

#pragma once

class Date
{
private:
    int day_;
    int month_;
    int year_;

    int parseDatePart(const QString &, const QString &);
    void validateDate();

public:
    Date(const QString *);

    QString toString() const;

    class InvalidDateFormat : public std::exception
    {
    private:
        std::string message_;

    public:
        InvalidDateFormat(const QString &);
        const char *what() const noexcept override;
    };

    class IncorrectDate : public std::exception
    {
    private:
        std::string message_;

    public:
        IncorrectDate(const QString &);
        const char *what() const noexcept override;
    };

    bool operator<(const Date &) const;
    bool operator>(const Date &) const;

    int getYear();
    int getMonth();
    int getDay();
};
