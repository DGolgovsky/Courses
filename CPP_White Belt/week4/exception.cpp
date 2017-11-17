#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <exception>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

void EnsureNextSymbolAndSkip(stringstream& stream) {
    if (stream.peek() != '/') {
        stringstream ss;
        ss << "expected / , but has: " << char(stream.peek());
        throw runtime_error(ss.str());
        //throw exception();
    }
    stream.ignore(1);
}
Date ParseDate(const string& s) {
    stringstream stream(s);
    Date date;
    //stream.peek();
    stream >> date.year;
    EnsureNextSymbolAndSkip(stream);
    stream >> date.month;
    EnsureNextSymbolAndSkip(stream);
    stream >> date.day;
    return date;
}

int main()
{
    string date_str = "2017.01/25";
    try {
    Date date = ParseDate(date_str);
    cout << setw(2) << setfill('0') << date.day << '.'
         << setw(2) << setfill('0') << date.month << '.'
         << date.year << endl;
    } catch (const exception& ex) {
        cout << "Exception: " << ex.what() << endl;
    }
    return 0;
}
