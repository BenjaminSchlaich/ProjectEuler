
#include <iostream>
using std::cout;
using std::endl;

#include "date.hpp"

int main()
{
    date dStart(1, 1, 1901);
    date dEnd(31, 12, 2000);

    cout << "counting days from " << dStart << " until " << dEnd << endl;

    int counter = 0;    // how many such target days are found
    int weekday = 2;    // 01.01.1901 was a tuesday, looked it up. (might also compute this easily, counting through, as we know that the 01.01.1900 was a monday)

    do
    {
        if(weekday == 7 && dStart.day == 1) // it's a sunday on the 1st! :D
            counter++;

        dStart++;
        weekday++;

        if(weekday == 8)                    // wrap around, s.t. after sunday comes monday.
            weekday = 1;
        
    }while(!(dStart == dEnd));              // count until the end day.

    cout << "counted " << counter << " sundays on the 1st in that span." << endl;
}
