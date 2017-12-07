#include <vector>
#include <iostream>
#include <string>

using std::vector;

template<typename T>
void print(std::string &&msg, T &&str, bool endl = 1)
{
    std::cout << msg << " :: " << str;
    if (endl)
        std::cout << std::endl;
    else
        std::cout << ", ";
}

int main()
{
    vector<int> v(16, 0);

    print("v.size()", v.size());            // 16
    print("v.capacity()", v.capacity());    // >= 16

    v.resize(32);           // v.size() = 32
    v.reserve(128);         // v.capacity() = 128

    vector<int>::iterator plc = v.begin();
    v.insert(plc+7, 23);
    v.erase(plc+1);

    v.push_back(42);        // insert to back
    v.pop_back();           // delete from back

    v[12] = 123;
    print("v[12]", v[12]);           // 123

    // C++03
    for (std::vector<int>::iterator it = v.begin();
         it != v.end(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;


    // C++11
    for (auto it = v.begin(); it != v.end(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;


    // C++03 :: Constant
    for (std::vector<int>::const_iterator it = v.cbegin();
         it != v.cend(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;

    // C++11 :: Reversed
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;


    return 0;
}
