#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<int> nums = {1,5,2,3,5};
    vector<string> str = {"one", "hello", "world", "milk"};
    int quantity = count(begin(nums), end(nums), 5);
    sort(begin(str), end(str));
    for (auto x : str) {
        cout << x << " ";
    }
    cout << "\n";
    cout << "There are: " << quantity << " fives";
    
    cout << "\n";
    return 0;
}
