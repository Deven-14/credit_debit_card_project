#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <exception>
#include "person.h"
#include "date.h"
#include "debitcard.h"
#include "creditcard.h"
#include "card.h"

using namespace std;

class BankAccount
{
	private:
		char bankAccountNumber[11];
		char pin[5];
		Person holder;
		Date creationDate;
		long double balance;
		
		bool validate(string &);
		long long hashPin(char[]);
		
		void getBankAccountNumber();
		void createBankAccountFile();
		void addToBankServer();
		void displayAssociatedCards(char);
		
		class WrongPin : public exception
		{
			public:
				WrongPin() {}
				const char* what();
		};
		
	public:
	
		BankAccount();
		BankAccount(string &);
		BankAccount(Card &, string);
		friend ostream& operator<<(ostream&, BankAccount&);
		friend istream& operator>>(istream&, BankAccount&);
		long double getBalance() { return balance; }
		void withdraw(long double);
		void deposit(long double);
		void edit();
		void displayAssociatedCreditCards();
		void displayAssociatedDebitCards();
};

#endif
