#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
using namespace std;

extern unordered_map<string, long long> cardServer;

extern unordered_map<string, long long> bankServer;

namespace CARD{

	bool server(string &cardNumber, long long pin);
	void startServer();
}

namespace BANK{

	bool server(string &bankAccNo, long long Pin);
	void startServer();
}

#endif
