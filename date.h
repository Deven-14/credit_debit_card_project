#ifndef DATE_H
#define DATE_H

#include <ctime>

using namespace std;

class Date
{
	private:
		int day, month, year;
		static time_t now;
		static tm *localTime;
	public:
		Date(int = localTime->tm_mday, int = (1 + localTime->tm_mon), int = (1900 + localTime->tm_year));
		Date(Date&, int, int);
		bool operator>=(Date&);
		friend ostream& operator<<(ostream&, Date&);
		//void edit(); no edit coz this date shouldn't be changed for a card and no input also, coz there should be no input from the user
};

#endif
