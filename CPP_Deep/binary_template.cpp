template <unsigned long N>
struct binary {
    static insigned const value
        = binary<N / 10>::value << 1 | N % 10;
};

template <> struct binary<0> {
    static unsigned const value = 0;
};

unsigned const one = binary<1>::value;
unsigned const three = binary<11>::value;
unsigned const five = binary<101>::value;

