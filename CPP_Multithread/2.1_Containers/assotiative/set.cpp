#include <iostream>
#include <set>
#include <unordered_set>

struct comparator
{
    bool operator()(const int &a, const int &b) const {
        return b < a;
    }
};

struct hasher
{
    size_t operator()(const int &a) const {
        return a % 2;
    }
};

int main(int argc, char **argv)
{
    std::set<int> s;
    std::unordered_set<int> us;

    std::set<int, comparator> cmp_s;
    std::unordered_set<int, hasher> hsr_us;

    s.insert(1);
    s.insert(3);
    s.insert(2);
    s.insert(5);
    s.insert(4);

    cmp_s.insert(1);
    cmp_s.insert(3);
    cmp_s.insert(2);
    cmp_s.insert(5);
    cmp_s.insert(4);

    us.insert(1);
    us.insert(3);
    us.insert(2);
    us.insert(5);
    us.insert(4);

    hsr_us.insert(1);
    hsr_us.insert(3);
    hsr_us.insert(2);
    hsr_us.insert(5);
    hsr_us.insert(4);

    std::cout << "std::set" << '\n';
    for (auto i = s.begin(); i != s.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::set - reversed" << '\n';
    for (auto i = s.rbegin(); i != s.rend(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::set - comparator" << '\n';
    for (auto i = cmp_s.begin(); i != cmp_s.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::unordered_set" << '\n';
    for (auto i = us.begin(); i != us.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::unordered_set - hasher" << '\n';
    for (auto i = hsr_us.begin(); i != hsr_us.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;

    return 0;
}
