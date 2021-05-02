#include <iostream>
#include <ctime>
#include <exception>
#include "date.h"
using namespace std;

time_t Date::now = time(0);
tm *Date::localTime = localtime(&now);

Date::Date(int day_, int month_, int year_) : day(day_), month(month_), year(year_) {}

Date::Date(Date &initial, int additionalMonth, int additionalYear)
{
	day = initial.day;
	year = initial.year + additionalYear;
	int temp = additionalMonth / 12;
	month = ( initial.month + additionalMonth ) % 12;
	year += temp;
}

ostream& operator<<(ostream &out, Date &eventDate)
{
	cout << "Date (DD/MM/YYYY) : ";
	if(eventDate.day < 10)
		cout << "0";
	cout << eventDate.day << "/";
	if(eventDate.month < 10)
		cout << "0";
	cout << eventDate.month << "/" << eventDate.year << endl;
	return out;
}

bool Date::operator>=(Date &d2)
{
	if(year > d2.year)
		return true;
	if(year == d2.year && month > d2.month)
		return true;
	if(year == d2.year && month == d2.month && day >= d2.day)
		return true;
	return false;
}

/*int main()
{
	Date d;
	cout << d;
	return 0;
}*/
