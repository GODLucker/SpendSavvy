#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "transaction.h"
#include "date.h"
using namespace std;
 
  
enum cards_type
{
	current,// ��� ������� ������������ ��������
	card, //�볺����, �� ��������� �������� �� ������������� �������� ������
	deposit,
	credit,
	other
};

class account
{
private:
	int id; //id
	string name; //����� �������
	string currency; //������
	string bank_name; //����� �����
	cards_type type; //��� ������
	float additional_analytics;//�������, ���� ������������ �� �������
	double remainder;//�������
	date date_create;
	date end_date;// �� ���� ������������ ���� ��������� �������� ��� �������.
	vector<transaction> all_transaction; //�� ���������� �� �����

	
public:
	account(int id, string name, string currency, string bank_name, cards_type type, float additional_analytics, double remainder, date date_create , date end_date);
	account(int id, string name, string currency, string bank_name, cards_type type, double remainder);
	account(const account& other);
	account(const account&& other)noexcept;
	account& operator=(const account& other);

	friend ostream& operator<<(ostream& out,const account& name); //�������������� ������ ��� ��'����
	std::ostream& print_short(std::ostream& out) const;
	
	
	vector<transaction>&get_tr();

	int get_id()const;
	void set_id(int id);

	string get_name();
	void set_name(string name);

	string get_currency();
	void set_currency(string currency);

	string get_bank_name();
	void set_bank_name(string bank_name);

	cards_type get_type();
	void set_type(cards_type type);

	cards_type get_Card() const;

	float get_additional_analytics();
	void set_additional_analytics(float additional_analytics);

	double get_remainder()const;
	void set_remainder(double remainder);

	date get_start_date()const;
	
	date get_end_date()const;
	void set_end_date(date end_date);

	string show_cards_type(const cards_type type) const;
	
	 
	double spending(double spending_money);
	double income(double income_money);
	
	double simple_percent(bool isLongYear)const;
	double deposit_interest(const date& start_date, const date& end_date) const;

	bool balance_checker();
	vector<transaction> get_tr_by_period(date start_p, date end_p);
	
};

 