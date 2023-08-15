#pragma once
#include "date.h"


enum transaction_type // перелік транзакцій
{
	spending, //витрати
	replenishment //поповнення
	};

class transaction // класс транзакція
{
private:
	float money; //  гроші
	transaction_type type; // тип транзакції
	date date_tr; // класс дати транзакцій

public:

	transaction();
	transaction(float money, transaction_type type, date date_tr);

	float get_money(); // доступ  до поля грошей
	transaction_type get_type(); // доступ до переліку транзакцій
	date get_date(); // доступ до поля дати классу дата
	string show_cards_type(const transaction_type type) const; // показати доступні картки
	friend ostream& operator<<(ostream& out, const transaction& transaction); // перегрузка виклику классу транзакція

	
};

 