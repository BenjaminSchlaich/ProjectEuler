
#include <iostream>

int daysInMonth(int month, int year);

struct date;

std::ostream &operator<<(std::ostream &os, date &d);

struct date
{
    friend std::ostream &operator<<(std::ostream &os, date &d);

    date(int day, int month, int year);

    void operator++(int);

    bool operator==(date &d);

    int day, month, year;
};
