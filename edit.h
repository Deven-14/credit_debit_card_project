#ifndef EDIT_H
#define EDIT_H

#include <vector>
using namespace std;

template<typename T>
class Edit
{
	private:
		char *str;
		int size;
		int prime;
		int multiplier;
		vector<long long> hashValues;
		long long hashFunc(char *, int);
		void preCompute();
		bool isEqual(char *, char *, int);
		long long getMultiplierPowerN(int n);
		string fileName;
	public:
		Edit();
		Edit(T &, string&);
		template<typename T2>
		void replace(T2 &, T2 &);
};

#include "edit_impl.h"//didn't put #ifndef and all in this header file, coz it's there in this file

#endif
