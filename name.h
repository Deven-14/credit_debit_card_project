#ifndef NAME_H
#define NAME_H

using namespace std;

class BankAccount;

template <typename T>
class Edit;

class Name
{
	private:
		char firstName[50], lastName[50];
	public:
		Name();
		friend istream& operator>>(istream&, Name&);
		friend ostream& operator<<(ostream&, Name&);
		void edit(Edit<BankAccount> &);
};

#endif
