#include <iostream>
#include <cstring>
#include "person.h"
#include "edit.h"

using namespace std;

Person::Person() : phoneNumber("0000000000") {}

istream& operator>>(istream &in, Person &user)
{
	cout << "Enter Person Details : " << endl << endl;
	in >> user.fullName;
	in >> user.permanentAddress;
	cout << "Phone Number (10 digits) : ";
	in >> user.phoneNumber;
	cout << endl;
	return in;
}

ostream& operator<<(ostream &out, Person &user)
{
	out << "Person Details : " << endl << endl;
	out << user.fullName;
	out << user.permanentAddress;
	cout << "Phone Number : " << user.phoneNumber << endl;
	cout << endl;
	return out;
}

void Person::edit(Edit<BankAccount> &file)
{
	int option = 6;
	do
	{
		cout << endl << "Edit Person Details : " << endl << endl;
		cout << "1. Name " << endl;
		cout << "2. Address " << endl;
		cout << "3. phoneNumber " << endl;
		cout << "4. Exit " << endl << endl;
		cout << "Enter Option : ";
		cin >> option;
		cout << endl;
		
		switch(option)
		{
			case 1 : 
				fullName.edit(file);
				break;
			case 2 :
				permanentAddress.edit(file);
				break;
			case 3 :
				char newPhoneNumber[11];
				cout << "Phone Number : ";
				cin >> newPhoneNumber;
				file.replace<char[11]>(phoneNumber, newPhoneNumber);
				break;
			case 4 :
				cout << "--Changes saved--" << endl;
				break;
			default : 
				cout << "Entered wrong option" << endl;
		}
		cout << endl;
		
	}while(option != 4);
	
	cout << "---Changed Person Details---" << endl << endl;
	cout << *this;
}

/*int main()
{
	Person user;
	cin >> user;
	cout << user;
	user.edit();
	return 0;
}*/
