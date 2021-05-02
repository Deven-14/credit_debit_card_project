#include <iostream>
#include <fstream>
#include "debitcardmenu.h"
#include "debitcard.h"

using namespace std;

void debitCardMenu()
{
	int option = 3;
	do{
	
		option = enterDebitCardMenuOption();
		goToSelectedDebitCardMenuOption(option);
		
	}while(option != 3);
	
}

int enterDebitCardMenuOption()
{
	int option;
	cout << endl << "-- Debit Card Menu --" << endl << endl;
	cout << "1. Create a New Debit Card " << endl;
	cout << "2. Login to an Existing Debit Card " << endl;
	cout << "3. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToSelectedDebitCardMenuOption(int option)
{
	switch(option)
	{
		case 1 :
			signUpDebitCard();
			break;
		case 2 :
			loginDebitCard();
			break;
		case 3 :
			cout << "-- Thank You -- " << endl;
			break;
		default :
			cout << "Entered Wrong Option, Please re-enter" << endl;
	}
}

void signUpDebitCard()
{
	try{
	
		DebitCard newCard;
		cout << newCard;
	
	}catch(...) {}
}

void loginDebitCard()
{
	try{
	
		string cardNumber;
		
		cout << "Enter your Debit Card Number : ";
		cin >> cardNumber;
		
		DebitCard existingCard(cardNumber);
		
		loginDebitCardMenu(existingCard);
	
	}catch(...) {}
}


void loginDebitCardMenu(DebitCard &card)
{
	int option = 5;
	
	do{
		
		option = getLoginDebitCardMenuOption();
		goToLoginDebitCardMenuOption(option, card);
	
	}while(option != 5);
	
}


int getLoginDebitCardMenuOption()
{
	int option;
	cout << endl << "-- Login Menu -- " << endl << endl;
	cout << "1. Show Details " << endl;
	cout << "2. WithDraw " << endl;
	cout << "3. Deposit " << endl;
	cout << "4. Statement " << endl;
	cout << "5. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToLoginDebitCardMenuOption(int option, DebitCard &card)
{
	switch(option)
	{
		case 1 :
			cout << card << endl;
			break;
		case 2 :
		{
			long double amount = 0;
			cout << "Enter the amount you want to WithDraw : ";
			cin >> amount;
			card.withdraw(amount);
			break;
		}
		case 3 :
		{
			long double amount = 0;
			cout << "Enter the amount you want to Deposit : ";
			cin >> amount;
			card.deposit(amount);
			break;
		}
		case 4 :
			card.getStatement();
			break;
		case 5 :
			cout << "Thank You " << endl;
			break;
		default :
			cout << "Entered Wrong Option, Please re-enter" << endl;
	}
}
