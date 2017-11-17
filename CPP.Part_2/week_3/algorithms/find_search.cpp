#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

std::initializer_list<std::string> getNames()
{
    return {"one", "two", "three"};
}

int main()
{
    std::vector<int> v = {2, 3, 5, 7, 13, 17, 19};
    size_t c = std::count_if(v.begin(), v.end(),
                             [](int x) {return x % 2 == 0;});
    auto it = std::lower_bound(v.begin(), v.end(), 11); // it -> 13

    bool has7 = std::binary_search(v.begin(), v.end(), 7); // true

    std::vector<std::string> db = getNames();
    std::for_each(db.begin(), db.begin() + db.size() / 2,
                  [](std::string &s){std::cout << s << '\n';});

    auto w = std::find(db.begin(), db.end(), "Waldo");

    std::string agents[3] = {"Alice", "Bob", "Eve"};
    auto it_agents = std::find_first_of(db.begin(), db.end(),
                                 agents, agents + 3);

    return 0;
}
