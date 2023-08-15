#pragma once
#include<iostream>
using namespace std;
class date
{
private:
	int day;
	int month;
	int year;

public:

	date();
	date(int day, int month, int year);

	int get_day()const;
	void set_day(int day);

	int get_month()const;
	void set_month(int month);


	int get_year()const;
	void set_year(int year);

    bool isLongYear()const;
	
	friend ostream& operator<<(ostream& out, const date& date);
	friend bool operator >=(const date& d1, const date& d2);
	friend bool operator <=(const date& d1, const date& d2);
	friend bool operator<(const date& d1, const date& d2);
	friend bool operator>(const date& d1, const date& d2);

	friend date operator-(const date& d1, const date& d2);
	
	
};

 