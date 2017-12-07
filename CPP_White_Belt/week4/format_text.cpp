/*
 * Информация
 * setw - задать ширину поля вывода
 * setprecision - точность вывода вещественных
 * setfill - "заполнитель" для setw
 * left - выравнивать данные по левому краю
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void print(const vector<string>& names,
           const vector<double> values,
           int width)
{
    for (const auto& n : names) {
        cout << setw(width) << n << ' ';
    }
    cout << endl;
    cout << fixed << setprecision(2);
    // cout << setw(10); reset after 1st output
    for (const auto& v : values) {
        cout << setw(width) << v << ' ';
    }
    cout << endl;
}

int main()
{
    vector<string> names = {"a", "b", "c"};
    vector<double> values = {5, 0.01, 0.000005};
    cout <<setfill('.');
    cout << left;
    print(names, values, 10);
    return 0;
}
