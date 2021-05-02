#include <iostream>
#include <cstring>
#include <fstream>
#include "statement.h"
using namespace std;

Statement::Statement(long double amt) : amount(amt) {}

Statement::Statement(long double amt, string pur) : amount(amt)
{
	strcpy(purpose, pur.c_str());
}

istream& operator>>(istream &in, Statement &transaction)
{
	cout << "Enter Purpose : ";
	in >> transaction.purpose;
	cout << endl;
	return in;
}

ostream& operator<<(ostream &out, Statement &transaction)
{
	out << "Statement : " << endl << endl;
	out << "Transaction Date : " << endl;
	out << transaction.transactionDate;
	out << "Transaction Amount : " << transaction.amount << endl;
	out << "Transaction Purpose : " << transaction.purpose << endl;
	out << endl;
	return out;
}

/*int main()
{
	Statement one(500);
	cin >> one;
	cout << one;
	return 0;
}*/
