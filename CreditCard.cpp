#include <iostream>
#include <fstream>
#include <cstring>
#include "edit.h"
#include "creditcard.h"
#include "server.h"
#include "bankaccount.h"
#include "statement.h"
using namespace std;

const char* CreditCard::OverLimit::what()
{
	return "CREDIT DECLINED - LIMIT EXCEEDED\n";
}

const char* CreditCard::WrongAmount::what()
{
	if(amount < 0)
		return "WRONG AMOUNT - IT CAN'T BE NEGATIVE\n";
	else
		return "WRONG AMOUNT - AMOUNT IS MORE THAN WHAT IS REQUIRED TO PAY\n";
}

CreditCard::CreditCard() : limit(40000), balance(39999), remainingAmtToPay(0)
{

	paymentDate = Date(26);
	if(Date() >= paymentDate)
		paymentDate = Date(paymentDate, 1, 0);

	createCreditCardFile();
	
	addToCardServer();
}

CreditCard::CreditCard(string &creditCardNo) : Card(creditCardNo)
{
	try{
	
		if(CARD::server(creditCardNo, hashPin(pin)) == false)
			throw WrongPin();
		
		string file = creditCardNo + ".txt";
		ifstream fin(file, ios::in);
		fin.read(reinterpret_cast<char*>(this), sizeof(CreditCard));
		fin.close();
		
	}catch(WrongPin &w)
	{
		cout << w.what() << endl;
		throw;
	}
}

bool CreditCard::validate()
{
	Date today;
	if(today >= expiryDate)
		return false;
	if(today >= paymentDate)
	{
		Date temp(26);
		if(today >= temp)
			paymentDate = Date(temp, 1, 0);
		else
			paymentDate = temp;
		pay(remainingAmtToPay);//pays full amount
		balance = limit - 1;//coz i'm having error in my Edit data structure
		remainingAmtToPay = 0;
	}
	return true;
}

inline bool CreditCard::validate(long double amount)
{
	return (amount >=0 && amount <= balance) ? true : false;
}	

void CreditCard::createCreditCardFile()
{
	string file = cardNumber;
	file += ".txt";
	ofstream fout(file);
	fout.write(reinterpret_cast<char*>(this), sizeof(CreditCard));
	fout.close();
	
	
	//after creating adding this to bank account file
	file.erase();
	file = bankAccountNumber;
	file += ".txt";
	
	fstream fout2(file, ios::in | ios::out | ios::app);
	char flag = '0';//0 is credit card, //1 is debit card
	fout2.write(reinterpret_cast<char*>(&flag), sizeof(char));
	fout2.write(reinterpret_cast<char*>(&cardNumber), sizeof(cardNumber));//sizeof(cN) will return 17 instead of 16, coz of \0 which is needed here
	fout2.close();
	
}

void CreditCard::credit(long double amount)
{
	try{
	
		if(!validate())
			throw CreditCard::Expired(expiryDate);
		if(!validate(amount))
			throw CreditCard::OverLimit(amount);
		
		cout << " -- Credit -- " << endl;
		
		//edit credit card file
		string fileName = cardNumber;
		fileName += ".txt";
		Edit<CreditCard> file(*this, fileName);
		
		long double newRemainingAmtToPay = remainingAmtToPay + amount;
		long double newBalance = balance - amount;
		
		file.replace<long double>(remainingAmtToPay, newRemainingAmtToPay);
		file.replace<long double>(balance, newBalance);
		
		//transaction details
		writeStatementIntoFile(amount);
		
	}
	catch(CreditCard::Expired &exp)
	{
		cout << exp.what();
	}
	catch(CreditCard::OverLimit &over)
	{
		cout << over.what();
	}
}

void CreditCard::pay(long double amount)
{
	try{
	
		if(!validate())
			throw CreditCard::Expired(expiryDate);
		if(amount > remainingAmtToPay || amount < 0)
			throw CreditCard::WrongAmount(amount);
			
		cout << " -- Pay -- " << endl;			
		
		//edit credit card file
		string fileName = cardNumber;
		fileName += ".txt";
		Edit<CreditCard> file(*this, fileName);
		
		long double newRemainingAmtToPay = remainingAmtToPay - amount;
		
		file.replace<long double>(remainingAmtToPay, newRemainingAmtToPay);
		
		//transaction details
		writeStatementIntoFile(amount, "pay");
		
		//changing bank account balance
		BankAccount(*this, bankAccountNumber).withdraw(amount);
		//instead of passing bankaccno, and amount to withdraw to server, we are withdrawing it here itself
		
	}
	catch(CreditCard::Expired &exp)
	{
		cout << exp.what();
	}
	catch(CreditCard::WrongAmount &wrng)
	{
		cout << wrng.what();
	}
}

ostream& operator<<(ostream &out, CreditCard &cCard)
{
	out << "Credit Card Details : " << endl << endl;
	out << "Bank Account Number : " << cCard.bankAccountNumber << endl;
	out << "Credit Card Number : " << cCard.cardNumber << endl;
	out << "Issue Date : " << endl << cCard.issueDate;
	out << "Expiry Date : " << endl << cCard.expiryDate;
	out << "CVV : " << cCard.cvv << endl;
	out << "Pin : " << cCard.pin << endl;
	out << "Limit : " << cCard.limit << endl;
	out << "Balance : " << cCard.balance << endl;
	out << "Remaining To Pay : " << cCard.remainingAmtToPay << endl;
	out << "Payment Date : " << endl << cCard.paymentDate;
	out << endl;
	return out;
}


void CreditCard::getStatement()
{
	string fileName = cardNumber;
	fileName += ".txt";
	
	ifstream fin(fileName);
	fin.seekg(0, ios::end);
	int endPosition = fin.tellg();
	
	fin.seekg(sizeof(CreditCard), ios::beg);
	
	Statement transaction;
	int count = 0;
	while(fin.tellg() != endPosition)
	{
		count++;
		fin.read(reinterpret_cast<char*>(&transaction), sizeof(Statement));
		cout << count << ". " << transaction;
	}
	
	fin.close();
}

/*int main()
{
	BANK::startServer();
	CARD::startServer();
	CreditCard c;
	c.credit(500);
	cout << c << endl;
	c.pay(200);
	cout << c << endl;
	string n;
	cout << "Enter the creditcardNO : ";
	cin >> n;
	CreditCard d(n);
	CreditCard e(d);
	cout << d;
	cout << e;
	d.credit(500);
	//e.credit(500);
	d.getStatement();
	return 0;
}*/
