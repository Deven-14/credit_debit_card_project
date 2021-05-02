#include <iostream>
#include <unordered_map>
#include <fstream>
#include "server.h"
using namespace std;

unordered_map<string, long long> cardServer;

unordered_map<string, long long> bankServer;

namespace CARD
{

	bool server(string &cardNumber, long long pin)
	{
		if(cardServer.find(cardNumber) == cardServer.end())
			return false;
		if(cardServer[cardNumber] != pin)
			return false;
		return true;
	}

	void startServer()
	{
		/*
		cardServer["0000000000000047"] = 267144685;//debit
		cardServer["0000000000000048"] = 267144685;//credit
		cardServer["0000000000000049"] = 267144685;//credit
		cardServer["0000000000000050"] = 267144685;//debit*/
		
		char acc[17];
		long long pin;
		
		fstream fin("createCardServer.txt", ios::in | ios::out | ios::app);
		fin.seekg(0, ios::end);
		
		int fileSize = fin.tellg();
		int size = 17 + sizeof(long long);
		int n = fileSize / size;
		
		fin.seekg(0, ios::beg);
		string accNo;
		
		for(int i = 0; i < n; ++i)
		{
			fin.read(reinterpret_cast<char*>(&acc), 17);
			fin.read(reinterpret_cast<char*>(&pin), sizeof(long long));
			accNo = acc;
			cardServer[accNo] = pin;
		}
		fin.close();
	}

}

namespace BANK
{

	bool server(string &bankAccNo, long long Pin)
	{
		if(bankServer.find(bankAccNo) == bankServer.end())
			return false;
		if(bankServer[bankAccNo] != Pin)
			return false;
		return true;
	}
	
	void startServer()
	{
		/*
		bankServer["0000000013"] = 267144685;//4200
		bankServer["0000000014"] = 267144685;//4200
		bankServer["0000000015"] = 267144685;//4200
		bankServer["0000000016"] = 267144685;//4200*/
		char acc[11];
		long long pin;
		
		fstream fin("createBankServer.txt", ios::in | ios::out | ios::app);
		fin.seekg(0, ios::end);
		
		int fileSize = fin.tellg();
		int size = 11 + sizeof(long long);
		int n = fileSize / size;
		
		fin.seekg(0, ios::beg);
		string accNo;
		
		for(int i = 0; i < n; ++i)
		{
			fin.read(reinterpret_cast<char*>(&acc), 11);
			fin.read(reinterpret_cast<char*>(&pin), sizeof(long long));
			accNo = acc;
			bankServer[accNo] = pin;
		}
		fin.close();
	}
	
}


/*int main()
{
	CARD::startServer();
	string acc = "0000000000000047";
	if(CARD::server(acc, 267144685) == true)
		cout << "true " << endl;
	return 0;
}*/
