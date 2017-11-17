auto u = make_unique<some_type>( some, parameters );
// a unique_ptr is move-only

go.run( [ u=move(u) ] { do_something_with( u ); } );
// move the unique_ptr into the lambda

int x = 4;
int z = [&r = x, y = x+1] {
            r += 2;         // set x to 6; "R is for Renamed Ref"
            return y+2;     // return 7 to initialize z
        }(); // invoke lambda

// C++11: have to state the parameter type
for_each( begin(v), end(v), [](const decltype(*begin(v))& x) {
            cout << x;
        } );
sort( begin(w), end(w), [](const shared_ptr<some_type>& a,
                           const shared_ptr<some_type>& b) {
            return *a<*b;
        } );
auto size = [](const unordered_map<wstring, vector<string>>& m) {
            return m.size();
        };

// C++14: just deduce the type
for_each( begin(v), end(v), [](const auto& x) { cout << x; } );
sort( begin(w), end(w), [](const auto& a, const auto& b) {
            return *a<*b;
        } );

// Cколько раз лямбда была вызвана:

auto lambda = [i=0]() mutable { return ++i; };

// Captures:
[], [x, &y], [&], [=], [&, x], [=, &z]
[x = std::move(y)] // from c++14

// Don't use [&], [=] like this:
std::function<bool(int)> getFilter(Checker const &c) {
    auto d = c.getModulo();
    // Captured reference to local variable
    return [&] (int i) { return i % d == 0; }
}

struct Checker {
    std::function<boll(int)> getFilter() const {
        // capture this, not d
        return [=] (int x) { return x % d == 0; } // x % this->d
    }
    int d;
}

