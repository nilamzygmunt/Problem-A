#include <iostream>
using namespace std;

// A date has day 'd', month 'm', year 'y', hour 'h', minute 'min, second 's'
struct Date {
    int d, m, y, h, min, s;
};

// To store number of days in 
// all months from January to Dec.
const int monthDays[12]
= { 31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31 };

// This function counts number of 
// leap years before the given date
int countLeapYears(Date d)
{
    int years = d.y;

    // Checking if we should consider this year in counting leap days
    if (d.m <= 2)
        years--;
  
    // An year is a leap year if it 
    // is a multiple of 4,
    // multiple of 400 and not a 
     // multiple of 100.
    return years / 4
        - years / 100
        + years / 400;

}//This function checks if we should count the last day or not
int checkTime(Date dt1, Date dt2)
{
    int day = 0;
    if (dt1.h < dt2.h)
        return 1;
    else if (dt1.h == dt2.h)
    {
        if (dt1.min < dt2.min)
            return 1;
        else if (dt1.min == dt2.min)
        {
            if (dt1.s < dt2.s || dt1.s == dt2.s)
                return 1;
        }
    }
    else return 0;
}

// This function returns number of 
// days between two given dates
int getDifference(Date dt1, Date dt2)
{
    // count the days before dt1

    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;

    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);
    
    //count the days before dt2

    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
    
    //Because we don't know if we can count the last day
    n2-= 1;
    n2 += checkTime(dt1, dt2);

    // return difference between two counts
    return (n2 - n1);
}


// Driver code
int main()
{
    int testsNumber;
    Date dt1, dt2;
    cin >> testsNumber;
    while (testsNumber--)
    {
        cin >> dt1.y >> dt1.m >> dt1.d >> dt1.h >> dt1.min >> dt1.s; 
        cin >> dt2.y >> dt2.m >> dt2.d >> dt2.h >> dt2.min >> dt2.s;
        cout << getDifference(dt1, dt2);
        cout << endl;
    } 

    return 0;
}