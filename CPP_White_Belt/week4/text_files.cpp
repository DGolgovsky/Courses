#include <iostream>
#include <fstream>

using namespace std;

void readAll (string& path) {
    ifstream input(path);
    //input.open("output.txt");
    if (input) {
        string line;
        while (getline(input, line)) {
            cout << line << endl;
        }
    }
    input.close();
}

int main()
{
    ifstream input("hello.txt");
    string path;
    string line;
    int year = 0;
    int month = 0;
    int day = 0;
    //if (input.is_open()) {
    if (input) {
        while (getline(input, line)) {
            cout << line << '\n';
        }
        cout << "done!" << endl;
    } else {
        cout << "error!" << '\n';
    }
    input.close();
    input.open("date.txt");
    if (input) {
        input >> year;
        input.ignore(1);
        input >> month;
        input.ignore(1);
        input >> day;
    }
    cout << year << '-' << month << '-' << day << '\n';

    path = "output.txt";
    ofstream output(path, ios::app);
    output << "Hello" << endl;
    readAll(path);
    return 0;
}
