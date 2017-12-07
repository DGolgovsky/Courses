#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <map>

using namespace std;

class Duration
{
private:
    int hour;
    int min;
public:
    Duration(int hour_ = 0, int min_ = 0) {
        int total = hour_ * 60 + min_;
        hour = total / 60;
        min = total % 60;
    }
    int Hour() const {
        return hour;
    }
    int Min() const {
        return min;
    }
};

bool operator<(const Duration& lhs,
               const Duration& rhs)
{
    if (lhs.Hour() == rhs.Hour()) {
        return lhs.Min() < rhs.Min();
    }
    return lhs.Hour() < rhs.Hour();
}

istream& operator>>(istream& is,
                    Duration& dur)
{
    int hour;
    is >> hour;
    is.ignore(1);
    int min;
    is >> min;
    dur = Duration(hour, min);
    return is;
}

ostream& operator<<(ostream& os, const Duration& dur) {
    os << setfill('0');
    os << setw(2) << dur.Hour() << ':'
       << setw(2) << dur.Min();
    return os;
}

Duration operator+(const Duration& lhs, const Duration& rhs) {
    return Duration {lhs.Hour() + rhs.Hour(), lhs.Min() + rhs.Min()};
}
int main()
{
    // Analogue of std::cin
    stringstream dur_ss("01:50");
    Duration dur1 {1, 12};
    Duration dur2 {1, 50};
    Duration worst;
    dur_ss >> dur1;
    cout << dur1 << endl;
    operator<<(operator<<(cout, "hello"), " world")<<endl;
    cout << boolalpha << (dur1 < dur2) << endl;
    cout << dur1 + dur2 << endl;
    vector<Duration> durations;
    durations.push_back(Duration{1, 50});
    durations.push_back(Duration{0, 50});
    durations.push_back(Duration{0, 1});
    for (const auto& dur : durations) {
        cout << dur << '\t';
    }
    cout << endl;
    sort(durations.begin(), durations.end());
    for (const auto& dur : durations) {
        cout << dur << '\t';
    }
    cout << endl;
// EPx04
    map<Duration, string> all;
    ifstream input("runners.txt");
    if (input) {
        Duration dur;
        string name; // better use set or vector
        while (input >> dur >> name) {
            if (worst < dur) {
                worst = dur;
            }
            all[dur] += (name + " ");
        }
    }
    ofstream out("result.txt");
    for (const auto& durNames : all) {
        out << durNames.first << '\t' << durNames.second << endl;
    }
    cout << "Worst runner: " << all[worst] << endl;

    return 0;
}
