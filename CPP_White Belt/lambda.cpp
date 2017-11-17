#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v {
        1, 3, 2, 5, 4
    };
    int thr = 0;
    cin >> thr;
    cout << count_if(begin(v), end(v), [thr](int x){
            if (x > thr) {
                return true;
            }
            return false;
            });
    cout << endl;

    return 0;
}
