#include <iostream>
#include <fstream>
using namespace std;

void getBankAccountNumber(char *bankAccountNumber)
{
    /*char temp[11];
	fstream fobj("bankAccountNumber.txt", ios::in | ios::out);
	for(int i = 0; i < 10; ++i)
	{
		fobj >> bankAccountNumber[i];
		temp[i] = bankAccountNumber[i];
	}
	temp[10] = bankAccountNumber[10] = '\0';
	int i = 9;
	while(bankAccountNumber[i] == '9')
		temp[i--] = '0';
	fobj.seekp(0, ios::beg);
	temp[i] = static_cast<char>(static_cast<int>(bankAccountNumber[i]) + 1);
	for(int i = 0; i < 10; ++i)
		fobj << temp[i];
	fobj.close();*/
	ofstream fout("debitCardNumber.txt");
	for(int i = 0; i < 16; ++i)
		fout << '0';
	fout.close();
}	

long long hashPin(char Pin[])
{
	int multiplier = 59789;
	int prime = 1000000009;
	long long hash = 0;
	for(int i = 0; i < 4; ++i)
		hash = ((hash * multiplier + Pin[i]) % prime + prime) % prime;
	return hash;
}

void createBankServer()
{
	char acc[11] = "0000000014";
	long long pin = 267144685;
	fstream fout("createBankServer.txt", ios::in | ios::out | ios::app);
	fout.write(reinterpret_cast<char*>(&acc), 11);
	fout.write(reinterpret_cast<char*>(&pin), sizeof(long long));
	fout.close();
}

void createCardServer()
{
	char acc[17] = "0000000000000047";
	long long pin = 267144685;
	fstream fout("createCardServer.txt", ios::in | ios::out | ios::app);
	fout.write(reinterpret_cast<char*>(&acc), 17);
	fout.write(reinterpret_cast<char*>(&pin), sizeof(long long));
	fout.close();
}

int main()
{
	//char a[11];
	//getBankAccountNumber(a);
	//char pin[5] = "5200";
	//long long a = hashPin(pin);
	//cout << a << endl;
	//createBankServer();
	createCardServer();
	return 0;
}
