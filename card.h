#ifndef CARD_H
#define CARD_H

#include <exception>
#include <unordered_map>
#include "date.h"

class BankAccount;

template <class T>
class Edit;

using namespace std;

class Card
{
	protected:
		char bankAccountNumber[11];
		char cardNumber[17];//16-digit card number
		Date issueDate, expiryDate;
		char pin[5];
		unsigned int cvv;
		long long hashPin(char[]);
		
		bool validate(char *);//to validate if it is correct bank Account
		//virtual bool validate() = 0;//to validate if the card is working
		//virtual bool validate(long double) = 0;//to validate if the money drawn is possible
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


#endif
