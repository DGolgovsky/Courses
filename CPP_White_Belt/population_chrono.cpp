#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Person
{
public:
    string name;
    string surname;
    int age;
};

vector<Person> GetMoscowPopulation();

void PrintPopulationSize(const vector<Person>& p)
{
    cout << "There are " << p.size() <<
        " peoples in Moscow" << endl;
}

int main()
{
    auto start = steady_clock::now();
    vector<Person> people = GetMoscowPopulation();
    auto finish = steady_clock::now();

    cout << "GetMoscowPopulation: "
        << duration_cast<milliseconds>(finish - start).count()
        << " ms" << endl;

    start = steady_clock::now();
    PrintPopulationSize(people);
    finish = steady_clock::now();
    cout << "PrintPopulationSize: "
        << duration_cast<milliseconds>(finish - start).count()
        << " ms" << endl;

    return 0;
}

vector<Person> GetMoscowPopulation()
{
    vector<Person> p;
    p.resize(12500000);
    return p;
    /* Below unused example of filling vector */
    for (int i = 0; i < 12500000; ++i) {
        p.push_back({"Unknown Name", "Unknown Surname", 0});
    }
    return p;
}
