#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include "card.h"
#include "server.h"
#include "statement.h"
#include "bankaccount.h"
#include "edit.h"

using namespace std;

bool Card::validate(char *bankAccNumber)
{
	string bankAccNo = bankAccNumber;
	char Pin[5];
	cout << "Enter your Bank Account Pin : ";
	cin >> Pin;
	if(BANK::server(bankAccNo, hashPin(Pin)) == false)
		return false;
	return true;
}

Card::Card() : expiryDate(issueDate, 0, 4)
{
	try{
	
		cout << "Enter your Bank Account Number (10 digits) : ";
		cin >> bankAccountNumber;
		
		if(!validate(bankAccountNumber))
			throw WrongPin();
		
		getCardNumber();
		cout << endl << "Enter a 4 Digit Pin for your new Card : ";
		cin >> pin;
	
		srand(time(0));
		cvv = rand()%10 * 100 + rand()%10 * 10 + rand()%10;
	
	}catch(WrongPin &w)
	{
		cout << w.what() << endl;
		throw;
	}
}

Card::Card(string &cardNo)
{
	cout << "Enter the Card Pin : ";
	cin >> pin;	
}

long long Card::hashPin(char Pin[])
{
	int multiplier = 59789;
	int prime = 1000000009;
	long long hash = 0;
	for(int i = 0; i < 4; ++i)
		hash = ((hash * multiplier + Pin[i]) % prime + prime) % prime;
	return hash;
}	

const char* Card::Expired::what()
{
	cout << "Expiry Date of this Card - " << endl;
	cout << expiryDate;
	return "--THIS CARD IS EXPIRED--\n" ;
}

const char* Card::WrongPin::what()
{
	return "-- Wrong Pin --\n";
}

void Card::addToCardServer()
{
	string cardNo = cardNumber;
	long long Pin = hashPin(pin);
	cardServer[cardNo] = Pin;
	
	fstream fout("createCardServer.txt", ios::in | ios::out | ios::app);
	fout.write(reinterpret_cast<char*>(&cardNumber), 17);
	fout.write(reinterpret_cast<char*>(&Pin), sizeof(long long));
	fout.close();
}

void Card::getCardNumber()
{
	char temp[17];
	
	fstream fobj("cardNumber.txt", ios::in | ios::out);
	
	for(int i = 0; i < 16; ++i)
	{
		fobj >> cardNumber[i];
		temp[i] = cardNumber[i];
	}
	
	temp[16] = cardNumber[16] = '\0';
	int i = 15;
	
	while(cardNumber[i] == '9')
		temp[i--] = '0';
	
	fobj.seekp(0, ios::beg);
	temp[i] = static_cast<char>(static_cast<int>(cardNumber[i]) + 1);
	
	for(int i = 0; i < 16; ++i)
		fobj << temp[i];
	
	fobj.close();
	/*ofstream fout("cardNumber.txt");
	for(int i = 0; i < 16; ++i)
		fout << '0';
	fout.close();*/
}

void Card::writeStatementIntoFile(long double amount)
{
	Statement transaction(amount);
	cin >> transaction;
	
	string fileName = cardNumber;
	fileName += ".txt";
	
	fstream fout(fileName, ios::in|ios::out|ios::app);
	fout.write(reinterpret_cast<char*>(&transaction), sizeof(Statement));
	fout.close();
}

void Card::writeStatementIntoFile(long double amount, string purpose)
{
	Statement transaction(amount, purpose);

	string fileName = cardNumber;
	fileName += ".txt";

	fstream fout(fileName, ios::in|ios::out|ios::app);
	fout.write(reinterpret_cast<char*>(&transaction), sizeof(Statement));
	fout.close();
}

/*int main()
{
	return 0;
}*/
