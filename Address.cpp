#include <iostream>
#include <cstring>
#include "address.h"
#include "edit.h"

using namespace std;

Address::Address() : houseNumber(0), pincode(0), street("NULL"), city("NULL"), state("NULL") {}

istream& operator>>(istream &in, Address &place)
{
	cout << "Enter Address : " << endl << endl;
	cout << "House Number : ";
	in >> place.houseNumber;
	cout << "Street : ";
	in.ignore();
	in.getline(place.street, 50);
	cout << "City : ";
	in.getline(place.city, 50);
	cout << "State : ";
	in.getline(place.state, 50);
	cout << "Pincode : ";
	in >> place.pincode;
	cout << endl;
	return in;
}

ostream& operator<<(ostream &out, Address &place)
{
	out << "Address : " << endl << endl;
	out << "House Number : " << place.houseNumber << endl;
	out << "Street : " << place.street << endl;
	out << "City : " << place.city << endl;
	out << "State : " << place.state << endl;
	out << "Pincode : " << place.pincode << endl;
	out << endl;
	return out;
}

void Address::edit(Edit<BankAccount> &file)
{
	int option = 6;
	do
	{
		cout << endl << "Edit Address : " << endl << endl;
		cout << "1. House Number " << endl;
		cout << "2. Street " << endl;
		cout << "3. City " << endl;
		cout << "4. State " << endl;
		cout << "5. Pincode " << endl;
		cout << "6. Exit " << endl << endl;
		cout << "Enter Option : ";
		cin >> option;
		cout << endl;
		
		switch(option)
		{
			case 1 : 
			{
				unsigned int newHouseNumber;
				cout << "Enter new House number : ";
				cin >> newHouseNumber;
				file.replace<unsigned int>(houseNumber, newHouseNumber);
				break;
			}
			case 2 :
			{
				char newStreet[50];
				cout << "Enter new Street : ";
				cin.ignore();
				cin.getline(newStreet, 50);
				file.replace<char[50]>(street, newStreet);
				break;
			}
			case 3 :
			{
				char newCity[50];
				cout << "Enter new City : ";
				cin.ignore();
				cin.getline(newCity, 50);
				file.replace<char[50]>(city, newCity);
				break;
			}
			case 4 :
			{
				char newState[50];
				cout << "Enter new State : ";
				cin.ignore();
				cin.getline(newState, 50);
				file.replace<char[50]>(state, newState);
				break;
			}
			case 5 : 
			{
				unsigned int newPincode;
				cout << "Enter new Pincode : ";
				cin >> newPincode;
				file.replace<unsigned int>(pincode, newPincode);
				break;
			}
			case 6 :
				cout << "--Changes saved--" << endl;
				break;
			default : 
				cout << "Entered wrong option" << endl;
		}
		cout << endl;
		
	}while(option != 6);
	
	cout << "---Changed Address---" << endl << endl;
	cout << *this;
}

/*int main()
{
	Address a;
	cin >> a;
	cout << a;
	a.edit();
	return 0;
}*/
