#ifndef PERSON_H
#define PERSON_H

#include "name.h"
#include "address.h"

class BankAccount;

template <typename T>
class Edit;

using namespace std;

class Person
{
	private:
		Name fullName;
		Address permanentAddress;
		char phoneNumber[11];
	public:
		Person();
		friend istream& operator>>(istream&, Person&);
		friend ostream& operator<<(ostream&, Person&);
		void edit(Edit<BankAccount> &);
};

#endif
