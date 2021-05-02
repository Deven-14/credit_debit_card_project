#ifndef DEBITCARD_H
#define DEBITCARD_H

#include <exception>
#include "card.h"
using namespace std;

class DebitCard : public Card
{
	private:
		long double balance;
		
		bool validate();
		bool validate(long double);//we need this function, in both debit and credit coz, balance points to two different memory location
		
		void createDebitCardFile();
		
		class BalanceExceeded : public exception
		{
			private:
				long double amount;
			public:
				BalanceExceeded(long double amt = 0) : amount(amt) {}
				const char* what();
		};
		
		class WrongAmount : public exception
		{
			private:
				long double amount;
			public:
				WrongAmount(long double amt = 0) : amount(amt) {}
				const char* what();
		};
		
	public:
	
		DebitCard();
		DebitCard(string &);
		void withdraw(long double);
		void deposit(long double);
		void getStatement();
		friend ostream& operator<<(ostream&, DebitCard&);
};

#endif
