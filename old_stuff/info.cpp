							Project - Credit and debit card class
							
Aim - To store bank account users info and allow transactions to be made via credit and debit cards


#include <iostream>
#include <cstring>
using namespace std;

//all these separate classes will go in separate file

class Name
{
	private:
		string firstName, lastName;
	public:
		Name(){}//parameterized constructor
		friend istream& operator>>(istream&, Name);
		friend ostream& operator<<(ostream&, Name);
		void edit();
};

class Address
{
	private:
		unsigned int houseNumber, pin;
		string state, city, street;
	public:
		Address(){}//parameterized constructor
		friend istream& operator>>(istream&, Address);
		friend ostream& operator<<(ostream&, Address);
		void edit();
};

class Date
{
	private:
		unsigned int day, month, year;
	public:
		Date(){}//parameterized constructor
		friend istream& operator>>(istream&, Date);
		friend ostream& operator<<(ostream&, Date);
		void edit();
};

class User
{
	private:
		Name holder;
		Address address;
		char phoneNumber[10];
	public:
		User(){}//parameterized constructor
		friend istream& operator>>(istream&, Date);
		friend ostream& operator<<(ostream&, Date);
		void edit();
};
		
class Card
{
	protected:
		char cardNumber[17];//16-digit card number
		User data;
		Date issueDate, expiryDate;
		unsigned int cvv;
		void createCard();
		int rowNumber;//row no of the card in the csv file
		int findRowNumber();
		bool validate() = 0;//to validate if the card is working
		bool validate(double) = 0;//to validate if the money to be drawn is possible
	public:
		Card(){}//parameterized constructor
		friend istream& operator>>(istream&, Card);
		friend ostream& operator<<(ostream&, Card);
		void edit();
};

class CreditCard : public Card
{
	private:
		unsigned double limit, balance, paid, remainingToPay;
		bool validate();
		bool validate(double);
	public:
		CreditCard() : limit(10000), balance(limit), paid(0), remainingToPay(0)
		{
			createCard();
		}
		CreditCard(char cardNo[])
		{
			rowNumber = findRowNUmber();
			validate();
		}
		void credit(double);
		void pay(double);
		friend ostream& operator<<(ostream&, CreditCard);
};

class DebitCard : public Card
{
	private:
		unsigned double balance;
		bool validate();
		bool validate(double);
	public:
		DebitCard() : balance(0)
		{
			createCard();
		}
		DebitCard(char cardNo[])
		{
			rowNumber = findRowNumber();
			validate();
		}
		void withDraw(double);
		void deposit(double);
		friend ostream& operator<<(ostream&, DebitCard);
};

void newUser()
{
	//create objects and input it in the csv file
}

void existingUser()
{
	//open file in read and write mode
	//using objects anc constructors to find the row and change the data in them by performing
	//desired operations
}

void Menu()
{
	cout << "Menu : " << endl;
	cout << "1. New user(Sign up) : " << endl;
	cout << "2. Existing user(Login) : " << endl;
	if(option == 1)
		newUser();
	else
		existingUser();
}



singleton class then make all the mem var refernces to the file itself

each person is a file,,, file name is credit/debit card number with hashfunction

and when editing the rabin karp can be used to speed up the process

each edit will directly be done to the file using the object 

fix phoneNumber, if 10 digits not enetered then make user reenter the phone number

change the autopayment on 26th on credit card......i.e if card used this month, then say this card's file and then at every 26th pay and then change the date


finish the edit method then put the pin verification in Card(string&) contructor

add pin to bank account class also

change the balance in debit card class, make it point to bank account class
