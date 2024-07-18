#include "date.hpp"

Date::Date(const QString *dateStr)
{
	static QRegularExpression regex("[-]");
	QStringList dateParts = dateStr->split(regex);

	if (dateParts.size() != 3)
	{
		throw InvalidDateFormat("Invalid date format. The date should have three parts separated by '-'");
	}

	day_ = parseDatePart(dateParts[0], "day");
	month_ = parseDatePart(dateParts[1], "month");
	year_ = parseDatePart(dateParts[2], "year");

	validateDate();
}

int Date::parseDatePart(const QString &part, const QString &partName)
{
	bool conversionSuccess = false;
	int value = part.toInt(&conversionSuccess);

	if (!conversionSuccess)
	{
		throw InvalidDateFormat("Invalid date format. " + partName + " is not a valid integer");
	}

	return value;
}

void Date::validateDate()
{
	if (year_ < 1 || year_ > 9999)
	{
		throw IncorrectDate("Invalid date. The year should be between 1 and 9999");
	}

	if (month_ < 1 || month_ > 12)
	{
		throw IncorrectDate("Invalid date. The month should be between 1 and 12");
	}

	if (day_ < 1 || day_ > 31)
	{
		throw IncorrectDate("Invalid date. The day should be between 1 and 31");
	}

	bool isLeapYear = (year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0);

	if (month_ == 2)
	{
		if (isLeapYear && day_ > 29 || !isLeapYear && day_ > 28)
		{
			throw IncorrectDate("Invalid date. February has " + QString::number(isLeapYear ? 29 : 28) + " days in this year");
		}
	}

	const int thirtyDayMonths[] = {4, 6, 9, 11};

	if (std::find(std::begin(thirtyDayMonths), std::end(thirtyDayMonths), month_) != std::end(thirtyDayMonths) && day_ > 30)
	{
		throw IncorrectDate("Invalid date. The month " + QString::number(month_) + " should have at most 30 days");
	}
}

bool Date::operator>(const Date &other) const
{
	if (year_ != other.year_)
	{
		return year_ > other.year_;
	}
	if (month_ != other.month_)
	{
		return month_ > other.month_;
	}
	return day_ > other.day_;
}

bool Date::operator<(const Date &other) const
{
	if (year_ != other.year_)
	{
		return year_ < other.year_;
	}
	if (month_ != other.month_)
	{
		return month_ < other.month_;
	}
	return day_ < other.day_;
}

int Date::getYear()
{
	return year_;
}

int Date::getMonth()
{
	return month_;
}

int Date::getDay()
{
	return day_;
}

QString Date::toString() const
{
	return QString::number(day_).rightJustified(2, '0') + '-' + QString::number(month_).rightJustified(2, '0') + '-' + QString::number(year_).rightJustified(4, '0');
}

Date::InvalidDateFormat::InvalidDateFormat(const QString &message) : message_(message.toStdString()) {}

const char *Date::InvalidDateFormat::what() const noexcept
{
	return message_.c_str();
}

Date::IncorrectDate::IncorrectDate(const QString &message) : message_(message.toStdString()) {}

const char *Date::IncorrectDate::what() const noexcept
{
	return message_.c_str();
}
