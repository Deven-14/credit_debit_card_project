#include <iostream>
#include <cfloat>
#include <fstream>
#include "debitcard.h"
#include "bankaccount.h"
#include "edit.h"
#include "server.h"
#include "statement.h"
using namespace std;

DebitCard::DebitCard()
{
	string fileName = bankAccountNumber;
	fileName += ".txt";
	balance = BankAccount(*this, bankAccountNumber).getBalance();;//indicating pin not required
	
	createDebitCardFile();
	
	addToCardServer();
}

DebitCard::DebitCard(string &debitCardNo) : Card(debitCardNo)
{
	try{
	
		if(CARD::server(debitCardNo, hashPin(pin)) == false)
			throw WrongPin();
		
		string file = debitCardNo + ".txt";
		ifstream fin(file, ios::in);
		fin.read(reinterpret_cast<char*>(this), sizeof(DebitCard));
		fin.close();
		
	}catch(WrongPin &w)
	{
		cout << w.what() << endl;
		throw;
	}
}

const char* DebitCard::BalanceExceeded::what()
{
	return "DEBIT DECLINED - NOT ENOUGH BALANCE\n";
}

const char* DebitCard::WrongAmount::what()
{
	if(amount < 0)
		return "WRONG AMOUNT - IT CAN'T BE NEGATIVE\n";
	else
		return "WRONG AMOUNT - AMOUNT IS MORE THAN NUMERIC LIMIT\n";
}

void DebitCard::createDebitCardFile()
{
	string file = cardNumber;
	file += ".txt";
	ofstream fout(file);
	fout.write(reinterpret_cast<char*>(this), sizeof(DebitCard));
	fout.close();
	
	//add this debit card to the bankaccount
	file.erase();
	file = bankAccountNumber;
	file += ".txt";
	
	fstream fout2(file, ios::in | ios::out | ios::app);
	char flag = '1';//0 is credit card, //1 is debit card
	fout2.write(reinterpret_cast<char*>(&flag), sizeof(char));
	fout2.write(reinterpret_cast<char*>(&cardNumber), sizeof(cardNumber));//sizeof(cN) will return 17 instead of 16, coz of \0 which is needed here
	fout2.close();
	
}

bool DebitCard::validate()
{
	Date today;
	if(today >= expiryDate)
		return false;
	return true;
}

inline bool DebitCard::validate(long double amount)
{
	return (amount >=0 && amount <= balance) ? true : false;
}

void DebitCard::withdraw(long double amount)
{
	try{
	
		if(!validate())
			throw DebitCard::Expired(expiryDate);
		if(!validate(amount))
			throw DebitCard::BalanceExceeded(amount);
			
		cout << " -- Withdraw -- " << endl;
		
		//edit debit card file
		string fileName = cardNumber;
		fileName += ".txt";
		Edit<DebitCard> file(*this, fileName);
		
		long double newBalance = balance - amount;
		
		file.replace<long double>(balance, newBalance);
		
		//transaction details
		writeStatementIntoFile(amount);
		
		//changing bank account balance
		BankAccount(*this, bankAccountNumber).withdraw(amount);
		
	}
	catch(DebitCard::Expired &exp)
	{
		cout << exp.what();
	}
	catch(DebitCard::BalanceExceeded &bal)
	{
		cout << bal.what();
	}
}

void DebitCard::deposit(long double amount)
{
	try{
	
		if(!validate())
			throw DebitCard::Expired(expiryDate);
		if(amount >= (LDBL_MAX - balance) || amount < 0)
			throw DebitCard::WrongAmount(amount);
		
		cout << " -- Deposit -- " << endl;
		
		//edit debit card file
		string fileName = cardNumber;
		fileName += ".txt";
		Edit<DebitCard> file(*this, fileName);
		
		long double newBalance = balance + amount;
		
		file.replace<long double>(balance, newBalance);
		
		//transaction details
		writeStatementIntoFile(amount, "deposit");
		
		//edit bank acc balance
		BankAccount(*this, bankAccountNumber).deposit(amount);
		
	}
	catch(DebitCard::Expired &exp)
	{
		cout << exp.what();
	}
	catch(DebitCard::WrongAmount &wrng)
	{
		cout << wrng.what();
	}
}

ostream& operator<<(ostream &out, DebitCard &dCard)
{
	out << "Debit Card Details : " << endl << endl;
	out << "Bank Account Number : " << dCard.bankAccountNumber << endl;
	out << "Debit Card Number : " << dCard.cardNumber << endl;
	out << "Issue Date : " << endl << dCard.issueDate;
	out << "Expiry Date : " << endl << dCard.expiryDate;
	out << "CVV : " << dCard.cvv << endl;
	out << "Balance : " << dCard.balance << endl;
	out << endl;
	return out;
}

void DebitCard::getStatement()
{
	string fileName = cardNumber;
	fileName += ".txt";
	
	ifstream fin(fileName);
	fin.seekg(0, ios::end);
	int endPosition = fin.tellg();
	
	fin.seekg(sizeof(DebitCard), ios::beg);
	
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
	DebitCard d;
	d.deposit(50);
	cout << d << endl;
	d.withdraw(20);
	cout << d << endl;
	string n;
	cout << "Enter the debitcardNO : ";
	cin >> n;
	DebitCard e(n);
	cout << e;
	e.getStatement();
	return 0;
}*/
