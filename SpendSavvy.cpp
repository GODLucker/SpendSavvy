//Copyright by Vlad Motyshen 2023

#include <iostream>
#include <string>
#include <sstream>
#include<chrono>
#include<ctime>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#endif
#ifdef _linux
#include <ncurses.h> // це бібліотека для розробки текстових інтерфейсів користувача
#endif

#include "include/account.h" //Наш головний класс

bool isUnsignedNumber(const std::string& str);//прототип на перевірку тільки чисел без знаку
bool isUnsignedNumber(int number);//прототип на перевірку тільки чисел без знаку
bool date_checker(int day, int month, int year);//прототип для перевірки на введеня дати(вискосність та інше)
bool is_valid_date(int day, int month, int year, const date& date_create);//прототип для перевірки введеної дати на меншість чи рівність дати створення рахунку
bool noexit=true; // Умова для меню
int main()
{
	int id = 1;
	int menu;
	auto now = std::chrono::system_clock::now(); //Отримуємо поточний час
	auto now_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&now_time_t);
	date date_create(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	
	std::vector<account> accountList;
	//FOR TEST 
	//date credit_end(1, 4, 2021);
	//date deposit_end;
	//account client1(0, "credit account", "UAH", "Monobank", credit, 16, -3000,date_create, credit_end);//test
	//account client2(2, "deposit account", "UAH", "Monobank", deposit, 16, 6000, date_create,credit_end);//test
	//
	//accountList.push_back(client1);
	//accountList.push_back(client2);
	 
	
	while(noexit)
	{
		cout << "-----------BANK ACCOUTN-----------\n";
		cout << "0 - Exit\n1 - Create account\n2 - Show avalibale card\n3 - Show info from avalible cards\n";
		cout << "4 - Save spending\n5 - Save replenishment\n6 - Check expenses and income from period \n";
		cin >> menu;
		switch (menu)
		{
		case 0:
		{
			cout << "See you soon!\t\n";
			noexit=false;
			break;
			
		}
		case 1:
		{
			int  type_card=0, day=0, month=0, year=0;;
			float first_deposit=0, year_percent=0;
			string bank_currency, bank_name, account_name;
			date deposit_end;
			date credit_end;
			cout << "\tYou choose create account!\n";
			cout << "Enter account name: ";
			cin >> account_name;
			cout << "Enter avalible currency UAH,USD,EUR. \n";
			cin >> bank_currency;
			while(true)
			{ 
				if (bank_currency != "UAH" && bank_currency != "USD" && bank_currency != "EUR")
				{
					cout << "Only capital letters!\nExample: Q W E R T..\n";
					cout << "Enter avalible currency UAH,USD,EUR: ";
					cin >> bank_currency;
					
				}
				else
					break;
			}
			cout << "Enter name of banking: " << endl;
			cin >> bank_name;
			cout << "Enter account card type\n";
			cout << "(0-Current account,1-card account,2-deposit account,3-credit account,4-other account) : ";
			cin >> type_card;
			if (type_card == 2 )//сторюємо депозитну картку
			{
				cout << "Enter year precent: \n";
				cin >> year_percent;

				cout << "Enter of date deposit ending.\n";
				cout << "Enter data: \nDay: ,Month: ,Year: \n";
				cin >> day >> month >> year;
				if(is_valid_date(day,month,year, date_create))// перевірка на коректність дати та перевірка кінцевої дати(не може бути менша чи дорівнювати дати створення карти
				{ 
				deposit_end= date(day, month, year);
				}
				else { cout << "\nWrong date! Try again!\n"; break; }
				cout << "Enter first ammount to deposit on your new account\n";
				cin >> first_deposit;
				
			}
			else if (type_card == 3) //сторюємо кредитну картку
			{
				cout << "Enter year precent: \n";
				cin >> year_percent;
				cout << "Enter of date credit ending: ";
				cout << "Enter data: \nDay: ,Month: ,Year: \n";
				cin >> day >> month >> year;
				if (is_valid_date(day, month, year, date_create))// перевірка на коректність дати 
				{
					date credit_end(day, month, year);
				}
				else { cout << "\nWrong date! Try again!\n"; break; }
				
				cout << "Enter first ammount to deposit on your new account\n";
				cin >> first_deposit;
			}
			else
			{ 
			cout << "Enter first ammount to deposit on your new account:\n";
			cin >> first_deposit;
			}
			while(true)
			{ 
			if (type_card != 2 && type_card != 3 && first_deposit >= 0)
			{

				account newaccount(id++, account_name, bank_currency, bank_name, cards_type(type_card),first_deposit);
				accountList.push_back(newaccount);
				break;
			}
			else if (type_card == 2 && first_deposit>=0)
			{
				account newaccount(id++, account_name, bank_currency, bank_name, cards_type(type_card), year_percent, first_deposit, date_create,deposit_end);
				accountList.push_back(newaccount);
				break;
			}
			else if (type_card == 3)
			{
				account newaccount(id++, account_name, bank_currency, bank_name, cards_type(type_card), year_percent, first_deposit, date_create, credit_end);
				accountList.push_back(newaccount);
				break;
			}
			else
				cout << "\n\tOnly credit account could have minus balance!\n";
			cout << "Enter first ammount to deposit on your new account\n";
			cin >> first_deposit;
			}
			break;


		}
		case 2:
		{
			cout << "You choose available card info:\n";

			if (accountList.empty()) {
				cout << "No accounts found.\n";
				break;
			}

			for (const auto& account : accountList) {
				cout << "\nCard ID:" << account.get_id() << " " << account.show_cards_type(account.get_Card()) << endl;
			}
			break;
		}
		case 3:
		{
			cout << "You choose show info from your avalible cards: \n";
			if (accountList.empty()) {
				cout << "No accounts found.\n";
				break;
			}
			for (const auto& accountlist : accountList)
			{
				if (accountlist.get_Card() == 0 || accountlist.get_Card() == 1 || accountlist.get_Card() == 4)
					accountlist.print_short(cout) << endl;
				else
					cout << accountlist << endl;
			}
			break;
		}
		case 4://Spending money
		{ 
			if (accountList.empty()) {
				cout << "No accounts found.\n";
				break;
			}
		
			int id, day, month, year;
			float spend_money;
			date date_tr;
			transaction_type::spending;
			cout << "Enter from what account minus spending: ";
			cout << "Your avalible account: \n";
			for (const auto& account : accountList)
			{
				cout << "\nCard ID:" << account.get_id() << " Type card: " << account.show_cards_type(account.get_Card()) << " Money: " << account.get_remainder() << endl;
			}
			cout << "Enter ID: ";
			cin >> id;
			for (auto i = 0; i < accountList.size(); i++)
			{
				if (accountList[i].get_id() == id)
				{
					cout << "\t\nAttention, if you have minus balance on credit card,you will pay 5% each transaction!\n";
					cout << "Enter the sum of spending: ";
					cin >> spend_money;
					if(accountList[i].balance_checker())
					{ 
					accountList[i].spending(spend_money);
					}
					else
					{
						accountList[i].spending(spend_money);
					}
					cout << "Enter data of spending: \nDay: ,Month: ,Year: \n";
					cin >> day >> month >> year;
					if (date_checker(day, month, year))// перевірка на коректність дати 
					{
					date date_tr(day, month, year);
					transaction tr(spend_money, spending, date_tr);
					accountList[i].get_tr().push_back(tr);
					}
					else { cout << "\nWrong date! Try again!\n"; break; }
					
					break;
				}
				else
				{
					cout << "Do not have entered ID in list\nTry again!\n";
					break;
				}

			}
			break;
		}
		case 5:
		{
			if (accountList.empty()) {
				cout << "No accounts found.\n";
				break;
			}
			cout << "You entered save replenishment!\n";
			int id, day, month, year;
			float replenishment_money;
			transaction_type::replenishment;
			cout << "Enter from what account plus replenishment. \n";
			cout << "Enter ID: \n";
			cout << "Your avalible account: \n";
			for (const auto& account : accountList)
			{
				cout << "\nCard ID:" << account.get_id() << " Type card: " << account.show_cards_type(account.get_Card()) << " Money: " << account.get_remainder() << endl;
			}
			cin >> id;
			for (auto i = 0; i < accountList.size(); i++)
			{
				if (accountList[i].get_id() == id)
				{
					cout << "Enter the sum of replenishment: ";
					cin >> replenishment_money;
					accountList[i].income(replenishment_money);
					cout << "Enter data of spending: \nDay: ,Month: ,Year: \n";
					cin >> day >> month >> year;
					if (date_checker(day, month, year))// перевірка на коректність дати 
					{
						date date_tr(day, month, year);
						transaction tr(replenishment_money, replenishment, date_tr);
						accountList[i].get_tr().push_back(tr);
					}
					else 
					{ 
						cout << "\nWrong date! Try again!\n";
						break;
					}			
					break;
				}
				else
				{
					cout << "Do not have entered ID in list\nTry again!\n";
					break;
				}
			}
			break;
		}
		case 6:
		{
			if (accountList.empty()) {
				cout << "No accounts found.\n";
				break;
			}
			int  day, month, year;
			date first_date, last_date;
			cout << "You choose report about transaction.\n";
			cout << "Enter first date: \nDay,month,year: ";
			cin >> day >> month >> year;
			if (date_checker(day, month, year))// перевірка на коректність дати 
			{
				 first_date=date(day, month, year);
				
				cout << "Enter last date: \nDay,month.year: ";
			
				cin >> day >> month >> year;
				if (date_checker(day, month, year))// перевірка на коректність дати 
				{
					 last_date=date(day, month, year);
					 if (last_date >= first_date)
					 {
						 for (auto i = 0; i < accountList.size(); i++)
						 {
							 vector<transaction> resList = accountList[i].get_tr_by_period(first_date, last_date);

							 for (const auto& res : resList)
							 {
								 cout << res;
							 }
						 }
					 }
					 else
					 {
						 cout << "\nWrong date! Try again!\n"; break;
					 }
				}else
				{ 
					cout << "\nWrong date! Try again!\n"; break;
				}
			}
			else 
			{ 
				cout << "\nWrong date! Try again!\n";
				break; 
			}
			
			
			break;
		}
		//	Тестування кейсів
		//case 7:
		//{
		//	int  day, month, year;
		//	
		//	cout << "You choose report about transaction.\n";
		//	cout << "Enter first date: \nDay,month.year: ";
		//	cin >> day >> month >> year;
		//		if (isUnsignedNumber(day) && isUnsignedNumber(month) && isUnsignedNumber(year))// Работает проверка на ввод только чисел по модулю
		//		{
		//	
		//		}else 
		//		{ 
		//		cout << "\nWrong date! Try again!\n";
		//		break; 
		//		}
		//	date first_date(day, month, year);
		//	cout << "Enter last date: \nDay,month.year: ";
		//	cin >> day >> month >> year;
		//		if(isUnsignedNumber(day)&& isUnsignedNumber(month)&& isUnsignedNumber(year))
		//		{ 
		//			if (is_valid_date(day, month, year))
		//			{
		//			}
		//			else { cout << "\nWrong date! Try again!\n"; break; }
		//			date last_date(day, month, year);
		//			vector<transaction> resList = client1.get_tr_by_period(first_date, last_date);
		//			for (const auto& res : resList)
		//			{
		//				cout << res;
		//			}
		//		}
		//		else 
		//		{ cout << "\nWrong date! Try again!\n"; break; }
		//	
		//break;
		//}
		default:
		{
			cout << "\nUnknown command!\n";
			break;
		}
		}

	}
	
}

bool is_valid_date(int day, int month, int year, const date& date_create) // Перевіряємо на коректність введену дату
{
	
	if (year < 1970) return false;
	if (month < 1 || month > 12) return false;

	if (month == 2) {
		if (year % 4 == 0) {
			if (day < 1 || day > 29) return false;
		}
		else {
			if (day < 1 || day > 28) return false;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day < 1 || day > 30) return false;
	}
	else {
		if (day < 1 || day > 31) return false;
	}

	// Перевіряємо, що введена дата не менше дати створення облікового запису
	auto deposit_end = date(day, month, year);
	return deposit_end >= date_create;
}
bool date_checker(int day, int month, int year)
{
	if (year >= 1970) {}

	else return false;

	if (month >= 1 && month <= 12) {}
	else return false;

	if (month == 2)
	{
		if (year % 4 == 0)
		{
			if (day >= 1 && day <= 29) day = day;
			else return false;
		}
		else
		{
			if (day >= 1 && day <= 28) day = day;
			else return false;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day >= 1 && day <= 30) day = day;
		else return false;
	}
	else
	{
		if (day >= 1 && day <= 31)
		{
			day = day;
		}
		else return false;
	}

	return true;
};

bool isUnsignedNumber(const std::string& str) {
	// Перевіряємо, що введений рядок містить лише цифри
	if (str.find_first_not_of("0123456789") == std::string::npos) {
		// Перетворимо рядок на беззнакове число
		std::stringstream ss(str);
		int number;
		ss >> number;
		return true;
	}
	else {
		return false;
	}
}

bool isUnsignedNumber(int number) {
	std::stringstream ss;
	ss << number;
	return isUnsignedNumber(ss.str());
}
