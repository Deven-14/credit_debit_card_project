//didn't put #ifndef and all in this header file, coz it's there in the edit.h
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "edit.h"
using namespace std;

template<typename T>
Edit<T>::Edit()
{
	cerr << "No object has been set to the edit method" << endl;
	exit(1);
}

template<typename T>
Edit<T>::Edit(T &obj, string &fileName_) : fileName(fileName_)
{
	str = reinterpret_cast<char*>(&obj);
	size = sizeof(obj);
	prime = 1000000009;
	srand(time(0));
	multiplier = (rand() % (prime-1)) + 1;
	preCompute();
}

template<typename T>
long long Edit<T>::hashFunc(char *subStr, int n)
{
	long long hash = 0;
	for(int i = 0; i < n; ++i)
		hash = ((hash * multiplier + subStr[i]) % prime + prime) % prime;
	return hash;
}

template<typename T>
long long Edit<T>::getMultiplierPowerN(int n)
{
	long long x = 1;
	for(int i = 1; i <= n; ++i)
		x = ((x * multiplier) % prime + prime) % prime;
	return x;
}

template<typename T>
void Edit<T>::preCompute()
{
	hashValues.reserve(size + 1);

	hashValues[0] = 0;
	
	for(int i = 1; i <= size; ++i)
		hashValues[i] = ((hashValues[i-1] * multiplier + str[i-1]) % prime + prime) % prime;
}


template<typename T>
bool Edit<T>::isEqual(char *str1, char *str2, int size)
{
	
	for(int i = 0; i < size; ++i)
		if(str1[i] != str2[i])
			return false;
	
	return true;
}

template <typename T>
template <typename T2>
void Edit<T>::replace(T2 &oldObj,T2 &newObj)
{
	int subStrSize = sizeof(oldObj);
	char *oldSubStr = reinterpret_cast<char*>(&oldObj);
	long long hashSubStr = hashFunc(oldSubStr, subStrSize);
	
	int n = size - subStrSize + 1;
	int index = -1;
	long long x = getMultiplierPowerN(subStrSize);
	
	for(int i = 0; i < n; ++i)
	{
		long long tempHash = (((hashValues[i + subStrSize] - hashValues[i] * x) % prime + prime) % prime);
		if(hashSubStr != tempHash)
			continue;
		if(!isEqual(str+i, oldSubStr, subStrSize))
			continue;
		index = i;
		break;
	}
	
	if(index == -1)
	{
		cout << "Couldn't replace" << endl;
		return;
	}
	
	char *newSubStr = reinterpret_cast<char*>(&newObj);
	for(int i = 0; i < subStrSize; ++i)
		str[index + i] = newSubStr[i];
	
	fstream file(fileName, ios::in | ios::out);
	file.seekp(0);
	file.seekp(index, ios::beg);
	file.write(newSubStr, subStrSize);
	file.close();
	
}

/*
#include <iostream>
#include <fstream>
using namespace std;

class abc
{
	public:
		int a;
		float b;
		double c;
		abc() : a(5), b(6.5), c(7.5) {}
};

int main()
{
	abc d;
	double e = 9.5;
	cout << d.a <<","<< d.b <<","<< d.c << endl;
	ofstream fout("omg.txt");
	fout.write(reinterpret_cast<char*>(&d), sizeof(abc));
	//fout1 << (char*)(&e);
	fout.close();
	fstream fout1("omg.txt", ios::in|ios::out);
	fout1.seekp(sizeof(int)+sizeof(float), ios::beg);
	cout << fout1.tellp();
	fout1.write((char*)(&e), sizeof(double));
	fout1.close();
	abc f;
	ifstream fin("omg.txt");
	fin.read(reinterpret_cast<char*>(&f), sizeof(abc));
	fin.close();
	cout << f.a <<","<< f.b <<","<< f.c << endl;
	return 0;
}
*/

/*class abc
{
	public:
		int a;
		float b;
		double c;
		abc() : a(5), b(6.5), c(7.5) {}
};

int main()
{
	abc d;
	ofstream fout("omg.txt");
	fout.write(reinterpret_cast<char*>(&d), sizeof(abc));
	fout.close();
	double e = 9.5;
	string file = "omg.txt";
	Edit<abc> t(d, file);
	t.replace<double>(d.c, e);
	cout << d.a <<","<< d.b <<","<< d.c << endl;
	abc f;
	ifstream fin("omg.txt");
	fin.read(reinterpret_cast<char*>(&f), sizeof(abc));
	fin.close();
	cout << f.a <<","<< f.b <<","<< f.c << endl;
	return 0;
}*/
