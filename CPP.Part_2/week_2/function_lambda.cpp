int mult(int x, int y)
{
    return x * y;
}

struct IntDiv
{
    int operator()(int x, int y) const {
        return x / y;
    }
};

// ...

std::function<int (int, int)> op;   // <ret_type (args)>

// ...

if (OP == '*')
    op = &mult;
else if (OP == '/')
    op = IntDiv();

int result = op(7, 8);

// Lambdas
std::function<int (int, int)> op =
    [](int x, int y) {
        return x / y;   // IntDiv
    }

// equals, w/ return type
op = [](int x, int y) -> int { return x / y; }

// C++14
op = [](auto x, auto y) { return x / y; }

int total = 0;
auto addToTotal = [&total](int x) { total += x; };

auto subTotal = [total](int &x) { x -= total; };

auto callUpdate = [this](){ this->update(); };

// Excercise 2.3.11
/*
 * Рассмотрим следующую функцию for_each:
 *
 * template<class F>
 * void for_each_int(int * p, int * q, F f) {
 *     for ( ; p != q; ++p )
 *         f(*p);
 * }
 * Определите переменную square_fun, хранящую безымянную функцию,
 * которая возводит переданное число в квадрат.
 * Пример:
 * int m[10] = {1,2,3,4,5,6,7,8,9,10};
 *
 * for_each_int(m, m + 10, square_fun);
 * // теперь m = {1,4,9,16,25,36,49,64,81,100};
 */
auto square_fun = [](int &p) {
    return p *= p;
};
