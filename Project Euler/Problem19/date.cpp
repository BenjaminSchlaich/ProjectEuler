
#include "date.hpp"

#include <iomanip>
using std::setw;

#include <iostream>
using std::cout;
using std::endl;

date::date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

void date::operator++(int)
{
    if(day == daysInMonth(month, year))
    {
        day = 1;

        if(month == 12)
        {
            month = 1;
            year++;
        }
        else
            month++;
    }
    else
        day++;
}

bool date::operator==(date &d)
{
    return day == d.day && month == d.month && year == d.year;
}

inline static bool isLeapYear(int year)
{
    return (year % 4 == 0) && ((!year % 100 == 0) || year % 400 == 0);
}

int daysInMonth(int month, int year)
{
    if(month < 1 || month > 12)
    {
        cout << "daysInMonth(): invalid month: " << month << "." << endl;
        return 0;
    }

    switch(month)
    {
       case 4:
       case 6:
       case 9:
       case 11: return 30;
       case 2: return isLeapYear(year) ? 29 : 28;
       default: return 31;
    }
}

std::ostream &operator<<(std::ostream &os, date &d)
{
    std::string yearString = std::to_string(std::abs(d.year));

    // prepend leading zeroes
    if(yearString.size() < 4)
        yearString = std::string(4-yearString.size(), '0') + yearString;
    
    if(d.year < 0)
        yearString += " b.c.";
    else
        yearString += " a.d.";

    os << setw(2) << d.day << "." << setw(2) << d.month << "." << yearString;

    return os;
}
