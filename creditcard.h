#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <exception>
#include "date.h"
#include "card.h"

using namespace std;

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

#endif
