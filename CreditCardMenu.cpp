#include <iostream>
#include <fstream>
#include "creditcardmenu.h"
#include "creditcard.h"

using namespace std;

void creditCardMenu()
{
	int option = 3;
	do{
	
		option = enterCreditCardMenuOption();
		goToSelectedCreditCardMenuOption(option);
		
	}while(option != 3);
	
}

int enterCreditCardMenuOption()
{
	int option;
	cout << endl << "-- Credit Card Menu --" << endl << endl;
	cout << "1. Create a New Credit Card " << endl;
	cout << "2. Login to an Existing Credit Card " << endl;
	cout << "3. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToSelectedCreditCardMenuOption(int option)
{
	switch(option)
	{
		case 1 :
			signUpCreditCard();
			break;
		case 2 :
			loginCreditCard();
			break;
		case 3 :
			cout << "-- Thank You -- " << endl;
			break;
		default :
			cout << "Entered Wrong Option, Please re-enter" << endl;
	}
}

void signUpCreditCard()
{
	try{
	
		CreditCard newCard;
		cout << newCard;
	
	}catch(...) {}
}

void loginCreditCard()
{
	try{
	
		string cardNumber;
		
		cout << "Enter your Credit Card Number : ";
		cin >> cardNumber;
		
		CreditCard existingCard(cardNumber);
		
		loginCreditCardMenu(existingCard);
	
	}catch(...) {}
}


void loginCreditCardMenu(CreditCard &card)
{
	int option = 5;
	
	do{
		
		option = getLoginCreditCardMenuOption();
		goToLoginCreditCardMenuOption(option, card);
	
	}while(option != 5);
	
}


int getLoginCreditCardMenuOption()
{
	int option;
	cout << endl << "-- Login Menu -- " << endl << endl;
	cout << "1. Show Details " << endl;
	cout << "2. Credit Amount" << endl;
	cout << "3. Pay Bill " << endl;
	cout << "4. Statement " << endl;
	cout << "5. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToLoginCreditCardMenuOption(int option, CreditCard &card)
{
	switch(option)
	{
		case 1 :
			cout << card << endl;
			break;
		case 2 :
		{
			long double amount = 0;
			cout << "Enter the amount you want to Credit : ";
			cin >> amount;
			card.credit(amount);
			break;
		}
		case 3 :
		{
			long double amount = 0;
			cout << "Enter the amount you want to Pay : ";
			cin >> amount;
			card.pay(amount);
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
