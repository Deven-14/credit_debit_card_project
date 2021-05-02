									
									Credit / Debit Card Project
									
Aim - To store bank account users info and allow transactions to be made via credit and debit cards
	
									
Concepts used :

OOP in C++

Abstract class
Concrete class
Exception handling with exception class

Compsition
Inhertance - Heirarchical

Funciton overloading
Funciton overriding
Friend functions
Operator overloading ( >> , << , >= ) with and without friend functions

Namespace
Class templates
Function templates

Reference variable
Static member variables and functions
Const variable
Extern variable

File handling
Dynamically making files

Hash Data Structure with class and function templates (edit.h and edit_impl.h)

template library (stl)
map data structure
vector data structure

modularizing files into header(.h) and source code(.cpp) files

Preprocessor directives (ifndef, endif, define) used in .h files



Structure of the Program : 

class Name
{
	private:
		char firstName[50], lastName[50];
	public:
		Name();
		friend istream& operator>>(istream&, Name&);
		friend ostream& operator<<(ostream&, Name&);
		void edit(Edit<BankAccount> &);
};


class Address
{
	private:
		unsigned int houseNumber, pincode;
		char street[50], city[50], state[50];
	public:
		Address();
		friend istream& operator>>(istream&, Address&);
		friend ostream& operator<<(ostream&, Address&);
		void edit(Edit<BankAccount> &);
};


class Date
{
	private:
		int day, month, year;
		static time_t now;
		static tm *localTime;
	public:
		Date(int = localTime->tm_mday, int = (1 + localTime->tm_mon), int = (1900 + localTime->tm_year));
		Date(Date&, int, int);
		bool operator>=(Date&);
		friend ostream& operator<<(ostream&, Date&);
};


class Person
{
	private:
		Name fullName;
		Address permanentAddress;
		char phoneNumber[11];
	public:
		Person();
		friend istream& operator>>(istream&, Person&);
		friend ostream& operator<<(ostream&, Person&);
		void edit(Edit<BankAccount> &);
};


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


class Card
{
	protected:
		char bankAccountNumber[11];
		char cardNumber[17];//16-digit card number
		Date issueDate, expiryDate;
		char pin[5];
		unsigned int cvv;
		long long hashPin(char[]);
		
		bool validate(char *);
		void getCardNumber();
		void addToCardServer();
		
		void writeStatementIntoFile(long double);
		void writeStatementIntoFile(long double, string);
		
		class WrongPin : public exception
		{
			public:
				WrongPin() {}
				const char* what();
		};
		
		class Expired : public exception
		{
			private:
				Date expiryDate;
			public:
				Expired() {}
				Expired(Date &exp) : expiryDate(exp) {}
				const char* what();
		};
		
	public:
		Card();
		Card(string &);
};


class CreditCard : public Card
{
	private:
		long double limit;
		long double balance, remainingAmtToPay;
		Date paymentDate;
		void createCreditCardFile();
		
		bool validate();
		bool validate(long double);
		
		class OverLimit : public exception
		{
			private:
				long double amount;
			public:
				OverLimit(long double amt = 0) : amount(amt) {}
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
		CreditCard();
		CreditCard(string &);
		void credit(long double);
		void pay(long double);
		void getStatement();
		friend ostream& operator<<(ostream&, CreditCard&);
};


class DebitCard : public Card
{
	private:
		long double balance;
		
		bool validate();
		bool validate(long double);
		
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


template<typename T>
class Edit
{
	private:
		char *str;
		int size;
		int prime;
		int multiplier;
		vector<long long> hashValues;
		long long hashFunc(char *, int);
		void preCompute();
		bool isEqual(char *, char *, int);
		long long getMultiplierPowerN(int n);
		string fileName;
	public:
		Edit();
		Edit(T &, string&);
		template<typename T2>
		void replace(T2 &, T2 &);
};


#include <unordered_map>
using namespace std;

extern unordered_map<string, long long> cardServer;

extern unordered_map<string, long long> bankServer;

namespace CARD{

	bool server(string &cardNumber, long long pin);
	void startServer();
}

namespace BANK{

	bool server(string &bankAccNo, long long Pin);
	void startServer();
}


class Statement
{
	private:
		Date transactionDate;
		long double amount;
		char purpose[50];
	public:
		Statement(long double = 0);
		Statement(long double, string);
		friend istream& operator>>(istream&, Statement&);
		friend ostream& operator<<(ostream&, Statement&);
};


#ifndef CREDITCARDMENU_H
#define CREDITCARDMENU_H

#include "creditcard.h"
using namespace std;

void creditCardMenu();
int enterCreditCardMenuOption();
void goToSelectedCreditCardMenuOption(int option);
void signUpCreditCard();
void loginCreditCard();
void loginCreditCardMenu(CreditCard &card);
int getLoginCreditCardMenuOption();
void goToLoginCreditCardMenuOption(int option, CreditCard &card);

#endif


#ifndef DebitCardMENU_H
#define DebitCardMENU_H

#include "debitcard.h"
using namespace std;

void debitCardMenu();
int enterDebitCardMenuOption();
void goToSelectedDebitCardMenuOption(int option);
void signUpDebitCard();
void loginDebitCard();
void loginDebitCardMenu(DebitCard &card);
int getLoginDebitCardMenuOption();
void goToLoginDebitCardMenuOption(int option, DebitCard &card);

#endif


#ifndef BANKACCOUNTMENU_H
#define BANKACCOUNTMENU_H

#include "bankaccount.h"
using namespace std;

void bankAccountMenu();
int enterBankAccountMenuOption();
void goToSelectedBankAccountMenuOption(int option);
void signUpBankAccount();
void loginBankAccount();
void loginBankAccountMenu(BankAccount &account);
int getLoginBankAccountMenuOption();
void goToLoginBankAccountMenuOption(int option, BankAccount &account);

#endif
