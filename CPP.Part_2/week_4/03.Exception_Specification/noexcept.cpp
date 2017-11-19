void no_throw() noexcept;
void may_throw();

// Copy constructor noexcept
struct NoThrow { int m[100] = {}; };

// Copy constructor noexcept(false)
struct MayThrow { std::vector<int> v; };

MayThrow mt;
NoThrow  nt;

bool a = noexcept(may_throw());     // false
bool b = noexcept(no_throw());      // true

bool c = noexcept(MayThrow(mt));    // false
bool d = noexcept(NoThrow(nt));     // true

// Conditional noexcept
template<class T, size_t N>
void swap(T (&a)[N], T (&b)[N])
    noexcept(noexcept(swap(*a, *b)));

template<class T1, class T2>
struct pair {
    void swap(pair & p)
        noexcept(noexcept(swap(first, p.first)) &&
                 noexcept(swap(second, p.second)))
        {
            swap(first, p.first);
            swap(second, p.second);
        }

    T1 first;
    T2 second;
};

