#include <iostream>

using namespace std;

struct Day {
    int value;
    explicit Day(int value_) {
        value = value_;
    }
};

struct Month {
    int value;
    explicit Month(int value_) {
        value = value_;
    }
};

struct Year {
    int value;
    explicit Year(int value_) {
        value = value_;
    }
};

struct Date{
    int day;
    int month;
    int year;
    Date(Day new_day, Month new_month, Year new_year) {
        day = new_day.value;
        month = new_month.value;
        year = new_year.value;
    }
};

void printDate(const Date& date)
{
    cout << date.day   << "."
         << date.month << "."
         << date.year  << "\n";
}

int main()
{
    // Not compile with explicit
    // Date date = {{10}, {11}, {17}};
    Date date = {Day(10), Month(11), Year(17)};
    printDate(date);
    return 0;
}
