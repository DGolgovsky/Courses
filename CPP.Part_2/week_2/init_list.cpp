template<typename T>
struct Array {
    Array(std::initializer_list<T> list);
};

Array<int> primes = {2, 3, 5, 7, 11, 13, 17};


int sum(std::initializer_list<int> list) {
    int result = 0;
    for (int x : list)
        result += x;
    return result;
}

int s = sum({1, 1, 2, 3, 5, 8, 13, 21});

