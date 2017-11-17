struct Person
{
    Person(string name, string surname)
        : name(name), surname(surname)
    {}
    string name;
    string surname;
};

bool operator==(Person const &a, Person const &b) {
    return a.name    == b.name
        && a.surname == b.surname;
}

namespace std {
    template <>
    struct hash<Person> { // specialization
        size_t operator()(Person const &p) const {
            hash<string> h;
            return h(p.name) ^ h(p.surname);
        }
    };
}

// uniq by name+surname
unordered_set<Person> s;

