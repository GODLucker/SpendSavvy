#include "account.h"
#include"date.h"
account::account(int id, string name, string currency, string bank_name, cards_type type, float additional_analytics, double remainder,date date_create, date end_date)
{
	
	this->id = id;
	this->name = name;
	this->currency = currency;
	this->bank_name = bank_name;
	this->type = type;
	this->additional_analytics = additional_analytics;
	this->remainder = remainder;
	this->date_create = date_create;
	this->end_date = end_date;
}

account::account(int id, string name, string currency, string bank_name, cards_type type, double remainder)
{
	this->id = id;
	this->name = name;
	this->currency = currency;
	this->bank_name = bank_name;
	this->type = type;
	this->remainder = remainder;
	
}


account::account(const account& other)
{
	id = other.id;
	currency = other.currency;
	name = other.name;
	bank_name = other.bank_name;
	type = other.type;
	additional_analytics = other.additional_analytics;
	remainder = other.remainder;
	date_create=other.date_create;
	end_date = other.end_date;
}

account::account(const account&& other) noexcept
{
	id = other.id;
	name = other.name;
	bank_name = other.bank_name;
	type = other.type;
	additional_analytics = other.additional_analytics;
	remainder = other.remainder;
	end_date = other.end_date;
}

account& account::operator=(const account& other)
{
	if (this == &other)
	{
		return *this;
	}
	id = other.id;
	currency = other.currency;
	name = other.name;
	bank_name = other.bank_name;
	type = other.type;
	additional_analytics = other.additional_analytics;
	remainder = other.remainder;
	end_date = other.end_date;
	return *this;
}



int account::get_id()const
{
	return id;
}

void account::set_id(int id)
{
	this -> id = id;
}

string account::get_name()
{
	return name;
}

void account::set_name(string name)
{
	this->name = name;
}

string account::get_currency()
{
	return currency;
}

void account::set_currency(string currency)
{
	this->currency = currency;
}

string account::get_bank_name()
{
	return bank_name;
}

void account::set_bank_name(string bank_name)
{
	this->bank_name = bank_name;
}

cards_type account::get_type()
{
	return type;
}

void account::set_type(cards_type type)
{
	this->type = type;
}

float account::get_additional_analytics()
{
	return additional_analytics;
}

void account::set_additional_analytics(float additional_analytics)
{
	this->additional_analytics = additional_analytics;
}

double account::get_remainder()const
{
	return remainder;
}

void account::set_remainder(double remainder)
{
	this->remainder = remainder;
}
date account::get_start_date()const
{
	return date_create;
}

date account::get_end_date()const
{
	return end_date;
}

void account::set_end_date(date end_date)
{
	this->end_date = end_date;
}

double account::spending(double spending_money)
{
	if(balance_checker())
	{ 
	return remainder = remainder - spending_money;
	}
	else
	{
		 remainder = abs(remainder - (spending_money + (spending_money * 0.5)));
		 return remainder = remainder * (-1);
	}
}

double account::income(double income_money)
{
	return remainder=remainder+income_money;
}

double account::simple_percent(bool isLongYear)const
{
	if(isLongYear)
	{ 
		
		return abs(((remainder * additional_analytics * 365) / 365) / 100);
	}
	else
	{
		return	abs(((remainder * additional_analytics * 366) / 366) / 100);
	}
}

double account::deposit_interest(const date& start_date, const date& end_date) const
{
	int months_in_year = 12;
	int total_months = (end_date.get_year() - start_date.get_year()) * months_in_year + (end_date.get_month() - start_date.get_month());
	if (end_date.get_day() < start_date.get_day())
	{
		total_months--;
	}
	double interest_rate = additional_analytics / 100;
	double interest = remainder * interest_rate * total_months / months_in_year;
	return interest;
}

//float account::monthly_precent()
//{
//	remainder=remainder * ((float (additional_analytics)/100) / 12);
//	return remainder;
//}
vector<transaction> account::get_tr_by_period(date start_p, date end_p)
{
	vector<transaction> result;

	for (int i = 0; i < all_transaction.size(); i++)
	{
		if (all_transaction[i].get_date() >= start_p && all_transaction[i].get_date() <= end_p)
		{
			result.push_back(all_transaction[i]);
		}
	}

	return result;
}
 string account::show_cards_type(const cards_type type) const 
{
	if (type == current)
	{
		return "current";
	}
	else if (type == card) {
		return "card";
	}
	else if (type == deposit) {
		return"deposit";
	}
	else if (type == credit) {
		return "credit";
	}

	return "other";

}
 bool account::balance_checker()
 {
	
	 if (get_remainder() >= 0)
		 return true;
	 else
		 return false;
 }
ostream& operator<<(ostream& out,const account& name)
{

	out << "Id: " << name.id << " \nBank account name: " << name.name << " \nCurrency: " << name.currency; // ID, ACCOUNT NAME ,CURRENCY
	out << "\nBank name: " << name.bank_name << "\nType card: " << name.show_cards_type(name.type); // BANK	NAME
	out << "\nAnalytics: " << name.additional_analytics << "%" << "\nAdditional sum : " << name.deposit_interest(name.get_start_date(),name.get_end_date()) << " " << name.currency;
	out << "\nRemainder: " << name.remainder << "\nData of start credit or deposit: " << name.date_create;
	out << "Data of end credit or deposit: " << name.end_date << endl;
	return out;
}
std::ostream& account::print_short(std::ostream& out) const	
{
	out << "Id: " << id << " \nBank account name: " << name << " \nCurrency: " << currency; // ID, ACCOUNT NAME ,CURRENCY
	out << "\nBank name: " << bank_name << "\nType card: " << show_cards_type(type); // BANK	NAME
	out << "\nRemainder: " << remainder << endl;
	return out;
}
vector<transaction>&account::get_tr()
{
	return all_transaction;
}
cards_type account::get_Card() const 
{
	return this->type;
}  