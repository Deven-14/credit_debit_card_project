#include <iostream>
#include <cstring>
#include "name.h"
#include "edit.h"
using namespace std;

Name::Name() : firstName("NULL"), lastName("NULL") {}

istream& operator>>(istream &in, Name &person)
{
	cout << "Enter Name : " << endl << endl;
	cout << "First Name : ";
	in >> person.firstName;
	cout << "Last Name : ";
	in >> person.lastName;
	cout << endl;
	return in;
}

ostream& operator<<(ostream &out, Name &person)
{
	out << "Name : " << endl << endl;
	out << "First Name : " << person.firstName << endl;
	out << "Last Name : " << person.lastName << endl;
	out << endl;
	return out;
}

void Name::edit(Edit<BankAccount> &file)
{
	int option = 6;
	do
	{
		cout << endl << "Edit Name : " << endl << endl;
		cout << "1. First Name " << endl;
		cout << "2. Last Name " << endl;
		cout << "3. Exit " << endl << endl;
		cout << "Enter Option : ";
		cin >> option;
		cout << endl;
		
		switch(option)
		{
			case 1 :
			{
				char newFirstName[50];
				cout << "Enter new First Name : ";
				cin.ignore();
				cin.getline(newFirstName, 50);
				file.replace<char[50]>(firstName, newFirstName);
				break;
			}
			case 2 :
			{
				char newLastName[50];
				cout << "Enter new Last Name : ";
				cin.ignore();
				cin.getline(newLastName, 50);
				file.replace<char[50]>(lastName, newLastName);
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
	
	cout << "---Changed Name---" << endl << endl;
	cout << *this;
	
}

/*int main()
{
	Name n;
	cin >> n;
	cout << n;
	n.edit();
	return 0;
}*/
