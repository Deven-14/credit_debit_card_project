#include <iostream>
#include "bankaccountmenu.h"
#include "creditcardmenu.h"
#include "debitcardmenu.h"
#include "server.h"

using namespace std;


int enterMenuOption()
{
	int option;
	cout << endl << "-- Menu --" << endl << endl;
	cout << "1. Bank Account " << endl;
	cout << "2. Credit Card " << endl;
	cout << "3. Debit Card " << endl;
	cout << "4. Exit " << endl << endl;
	cout << "Enter Option : ";
	cin >> option;
	cout << endl;
	return option;
}

void goToSelectedMenuOption(int option)
{
	switch(option)
	{
		case 1 :
			bankAccountMenu();
			break;
		case 2 :
			creditCardMenu();
			break;
		case 3 :
			debitCardMenu();
			break;
		case 4 :
			cout << "-- Thank You -- " << endl;
			break;
		default :
			cout << "Entered Wrong Option, Please re-enter" << endl;
	}
}

void Menu()
{
	int option = 4;
	do{
	
		option = enterMenuOption();
		goToSelectedMenuOption(option);
		
	}while(option != 4);
	
}


int main()
{
	BANK::startServer();
	CARD::startServer();
	Menu();
	return 0;
}
