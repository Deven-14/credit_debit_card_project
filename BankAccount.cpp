#include <iostream>
#include <fstream>
#include <cstring>
#include "bankaccount.h"
#include "person.h"
#include "edit.h"
#include "server.h"
using namespace std;

BankAccount::BankAccount() : creationDate(), balance(0) 
{
	getBankAccountNumber();
}


BankAccount::BankAccount(string &bankAccNo)
{
	try{
	
		if(!validate(bankAccNo))
			throw WrongPin();
		
		string file = bankAccNo + ".txt";
		ifstream fin(file, ios::in);
		fin.read(reinterpret_cast<char*>(this), sizeof(BankAccount));
		fin.close();
	
	}catch(WrongPin &w)
	{
		cout << w.what() << endl;
		throw; //rethrowing so that the statements after that won't work
	}
}


BankAccount::BankAccount(Card &card, string bankAccNo)
{
	string fileName = bankAccNo;
	fileName += ".txt";
	ifstream fin(fileName, ios::in);
	fin.read(reinterpret_cast<char*>(this), sizeof(BankAccount));
	fin.close();
}


bool BankAccount::validate(string &bankAccNo)
{
	char Pin[5];
	cout << "Enter the Bank Account Pin : ";
	cin >> Pin;
	if(BANK::server(bankAccNo, hashPin(Pin)) == false)
		return false;
	return true;
}

long long BankAccount::hashPin(char Pin[])
{
	int multiplier = 59789;
	int prime = 1000000009;
	long long hash = 0;
	for(int i = 0; i < 4; ++i)
		hash = ((hash * multiplier + Pin[i]) % prime + prime) % prime;
	return hash;
}	

const char* BankAccount::WrongPin::what()
{
	return "-- Wrong Pin --\n";
}


void BankAccount::getBankAccountNumber()
{
    char temp[11];
	fstream fobj("bankAccountNumber.txt", ios::in | ios::out);
	
	for(int i = 0; i < 10; ++i)
	{
		fobj >> bankAccountNumber[i];
		temp[i] = bankAccountNumber[i];
	}
	
	temp[10] = bankAccountNumber[10] = '\0';
	
	int i = 9;
	while(bankAccountNumber[i] == '9')
		temp[i--] = '0';
		
	fobj.seekp(0, ios::beg);
	temp[i] = static_cast<char>(static_cast<int>(bankAccountNumber[i]) + 1);
	
	for(int i = 0; i < 10; ++i)
		fobj << temp[i];
		
	fobj.close();
	/*ofstream fout("bankAccountNumber.txt");
	for(int i = 0; i < 10; ++i)
		fout << '0';
	fout.close();*/
}


void BankAccount::createBankAccountFile()
{
	string file = bankAccountNumber;
	file += ".txt";
	ofstream fout(file);
	fout.write(reinterpret_cast<char*>(this), sizeof(BankAccount));
	fout.close();
}


void BankAccount::addToBankServer()
{
	string bankAccNo = bankAccountNumber;
	long long Pin = hashPin(pin);
	bankServer[bankAccNo] = Pin;
	
	fstream fout("createBankServer.txt", ios::in | ios::out | ios::app);
	fout.write(reinterpret_cast<char*>(&bankAccountNumber), 11);
	fout.write(reinterpret_cast<char*>(&Pin), sizeof(long long));
	fout.close();
}

istream& operator>>(istream &in, BankAccount &newAccount)
{
	cout << "Enter Bank Account Details : " << endl << endl;
	in >> newAccount.holder;
	cout << "Initial deposit : ";
	in >> newAccount.balance;
	cout << endl;
	cout << "Enter a 4 Digit Pin for your new Bank Account : ";
	cin >> newAccount.pin;
	
	newAccount.createBankAccountFile();
	
	newAccount.addToBankServer();
	
	return in;
}

ostream& operator<<(ostream &out, BankAccount &newAccount)
{
	out << "BankAccount Details: " << endl << endl;
	out << "Account Number : " << newAccount.bankAccountNumber << endl;
	out << "Pin : " << newAccount.pin << endl;
	out << newAccount.holder;
	out << newAccount.creationDate;
	out << "Balance : " << newAccount.balance << endl;
	out << "Pin : " << newAccount.pin << endl;
	out << endl;
	return out;
}


void BankAccount::withdraw(long double amount)
{
	string fileName = bankAccountNumber;
	fileName += ".txt";
	
	Edit<BankAccount> file(*this, fileName);	
	long double newBalance = balance - amount;
	
	file.replace<long double>(balance, newBalance);
}


void BankAccount::deposit(long double amount)
{
	string fileName = bankAccountNumber;
	fileName += ".txt";
	
	Edit<BankAccount> file(*this, fileName);	
	long double newBalance = balance + amount;
	
	file.replace<long double>(balance, newBalance);
}


void BankAccount::edit()
{
	string fileName = bankAccountNumber;
	fileName += ".txt";
	Edit<BankAccount> file(*this, fileName);
	
	int option = 3;
	do
	{
		cout << endl << "Edit BankAccount Details : " << endl << endl;
		cout << "1. Holder Details " << endl;
		cout << "2. Balance " << endl;
		cout << "3. Exit " << endl << endl;
		cout << "Enter Option : ";
		cin >> option;
		cout << endl;
		
		switch(option)
		{
			case 1 :
				holder.edit(file);
				break;
				
			case 2 :
			{
				long double newBalance;
				cout << "Enter new Balance : ";
				cin >> newBalance;
				file.replace<long double>(balance, newBalance);
				break;
			}
			
			case 3 :
				cout << "--Changes saved--" << endl;
				break;
				
			default : 
				cout << "Entered wrong option" << endl;
				
		}
		cout << endl;
		
	}while(option != 3);
	
	cout << "---Changed BankAccount---" << endl << endl;
	cout << *this;
}

void BankAccount::displayAssociatedCards(char type)
{
	string fileName = bankAccountNumber;
	fileName += ".txt";
	char flag, cardNumber[17];
	
	ifstream fin(fileName);
	
	fin.seekg(0, ios::end);
	int endPosition = fin.tellg();
	
	fin.seekg(sizeof(BankAccount), ios::beg);
	int count = 0;
	while(fin.tellg() != endPosition)
	{
		fin.read(reinterpret_cast<char*>(&flag), sizeof(char));
		fin.read(reinterpret_cast<char*>(&cardNumber), 17);
		
		if(flag == type)
		{
			count++;
			cout << count << ". " <<  cardNumber << endl;
		}
	}
	
	fin.close();
	cout << endl;
}

void BankAccount::displayAssociatedCreditCards()
{
	cout << "The Associated CreditCard Numbers are : " << endl;
	displayAssociatedCards('0');
}

void BankAccount::displayAssociatedDebitCards()
{
	cout << "The Associated DebitCard Numbers are : " << endl;
	displayAssociatedCards('1');
}

/*int main()
{
	BANK::startServer();
	CARD::startServer();
	BankAccount b;
	cin >> b;
	cout << b;
	b.edit();
	string bAcc;
	cout << "Enter b acc no" << endl;
	cin >> bAcc;
	BankAccount c(bAcc);
	cout << c;
	c.displayAssociatedCreditCards();
	c.displayAssociatedDebitCards();
	return 0;
}*/
