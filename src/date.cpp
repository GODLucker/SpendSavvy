#include "date.h"

date::date()
{
	day = 1;
	month = 1;
	year = 1900;
}

date::date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

int date::get_day()const
{
	return day;
}

void date::set_day(int day)
{
	this->day = day;
}

int date::get_month()const
{
	return month;
}

void date::set_month(int month)
{
	this->month = month;
}

int date::get_year()const
{
	return year;
}

void date::set_year(int year)
{
	this->year = year;
}

 bool date::isLongYear()const
{
	
	return (year % 4 == 0 || (year % 100 == 0 && year % 400));

}

 

ostream& operator<<(ostream& out, const date& date)
{
	return out << " Day: " << date.day << " Month: " << date.month << " year: " << date.year << endl;
}

bool operator>=(const date& d1, const date& d2)
{
	if (d1.year > d2.year)
	{
		return true;
	}
	else if (d1.year == d2.year)
	{
		if (d1.month > d2.month)
		{
			return true;
		}
		else if (d1.month == d2.month)
		{
			if (d1.day >= d2.day)
			{
				return true;
			}
		}
	}

	return false;
}

bool operator<=(const date& d1, const date& d2)
{
	if (d1.year < d2.year)
	{
		return true;
	}
	else if (d1.year == d2.year)
	{
		if (d1.month < d2.month)
		{
			return true;
		}
		else if (d1.month == d2.month)
		{
			if (d1.day <= d2.day)
			{
				return true;
			}
		}
	}

	return false;
}
bool operator<(const date& d1, const date& d2) {
	if (d1.year < d2.year) {
		return true;
	}
	else if (d1.year == d2.year && d1.month < d2.month) {
		return true;
	}
	else if (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day) {
		return true;
	}
	return false;
}

bool operator>(const date& d1, const date& d2) {
	return d2 < d1;
}
date operator-(const date& d1, const date& d2) {
	int dayDiff = d1.day - d2.day;
	int monthDiff = d1.month - d2.month;
	int yearDiff = d1.year - d2.year;

	return date(dayDiff, monthDiff, yearDiff);
}

