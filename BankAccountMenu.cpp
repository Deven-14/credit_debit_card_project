#include <iostream>
#include <fstream>
#include "bankaccountmenu.h"
#include "bankaccount.h"
using namespace std;

void bankAccountMenu()
{
	int option = 3;
	do{
	
		option = enterBankAccountMenuOption();
		goToSelectedBankAccountMenuOption(option);
		
	}while(option != 3);
	
}

int enterBankAccountMenuOption()
{
	int option;
	cout << endl << "--Bank Account Menu --" << endl << endl;
	cout << "1. Sign Up (Create New Bank Account) " << endl;
	cout << "2. Login to Existing Bank Account " << endl;
	cout << "3. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToSelectedBankAccountMenuOption(int option)
{
	switch(option)
	{
		case 1 :
			signUpBankAccount();
			break;
		case 2 :
			loginBankAccount();
			break;
		case 3 :
			cout << "-- Thank You -- " << endl;
			break;
		default :
			cout << "Entered Wrong Option, Please re-enter" << endl;
	}
}

void signUpBankAccount()
{
	BankAccount newAccount;
	cin >> newAccount;
	cout << newAccount;
	newAccount.edit();
}


void loginBankAccount()
{
	try{
	
		string bankAccountNumber;
		
		cout << "Enter your Bank Account Number : ";
		cin >> bankAccountNumber;
		
		BankAccount existingAccount(bankAccountNumber);
		
		loginBankAccountMenu(existingAccount);
	
	}catch(...) {}
}


void loginBankAccountMenu(BankAccount &account)
{
	int option = 5;
	
	do{
		
		option = getLoginBankAccountMenuOption();
		goToLoginBankAccountMenuOption(option, account);
	
	}while(option != 5);
	
}


int getLoginBankAccountMenuOption()
{
	int option;
	cout << endl << "-- Login Menu -- " << endl << endl;
	cout << "1. Show Details " << endl;
	cout << "2. Edit " << endl;
	cout << "3. Display associated Credit Cards " << endl;
	cout << "4. Display associated Debit Cards " << endl;
	cout << "5. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToLoginBankAccountMenuOption(int option, BankAccount &account)
{
	switch(option)
	{
		case 1 :
			cout << account << endl;
			break;
		case 2 :
			account.edit();
			break;
		case 3 :
			account.displayAssociatedCreditCards();
			break;
		case 4 :
			account.displayAssociatedDebitCards();
			break;
		case 5 :
			cout << "Thank You " << endl;
			break;
		default :
			cout << "Entered Wrong Option, Please re-enter" << endl;
	}
}
