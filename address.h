#ifndef ADDRESS_H
#define ADDRESS_H

using namespace std;

class BankAccount;

template <typename T>
class Edit;

class Address
{
	private:
		unsigned int houseNumber, pincode;
		char street[50], city[50], state[50];
	public:
		Address();
		friend istream& operator>>(istream&, Address&);
		friend ostream& operator<<(ostream&, Address&);
		void edit(Edit<BankAccount> &);
};

#endif
