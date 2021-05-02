#ifndef STATEMENT_H
#define STATEMENT_H

#include "date.h"
using namespace std;

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

#endif
