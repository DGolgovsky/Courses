Array<Unit*> units;

for (size_t i = 0; i != units.size(); ++i) {
    // Unit *
    auto u = units[i];

    // Array<Item> const &
    decltype(u->items()) items = u->items;
    // ...

    auto a = items[0];          // a - Items
    decltype(items[0]) b = a;   // b - Item const &

    decltype(a) c = a;          // c - Item
    decltype((a)) d = a;        // d - Item &

    decltype(b) e = b;          // e - Item const &
    decltype((b)) f = b;        // f - Item const &
}

// RETURN_TYPE = ?
template<typename A, typename B>
RETURN_TYPE Plus(A a, B b) { return a + b; }

// Incorrect. a and b defined later
template<typename A, typename B>
decltype(a + b) Plus(A a, B b) { return a + b; }

// C++11
template<typename A, typename B>
auto Plus(A a, B b) -> decltype(a + b) {
    return a + b;
}

// C++14
template<typename A, typename B>
auto Plus(A a, B b) {
    return a + b;
}
