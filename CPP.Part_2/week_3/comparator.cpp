struct Person { string name; string surname; }

bool operator<(Person const &a, Person const &b) {
    return a.name < b.name ||
          (a.name == b.name && a.surname < b.surname);
}
// uniq by name+surname
std::set<Person> s1; // std::set<T, std::less>

struct PersonComp {
    bool operator()(Person const& a,
                    Person const &b) const {
        return a.surname < b.surname;
    }
};
// uniq by surname
std::set<Person, PersonComp> s2;

