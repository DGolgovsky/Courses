/*
 * Выберите все случаи, где преобразование static_cast<> в
 * правой части обязательно.
 */

struct Number {};

struct BigInt : Number
{
    BigInt(int x);
};

struct String
{
    explicit String(char const * s);
};

int main()
{
    int a = static_cast<int>(3.5);
    double b = static_cast<double>(7);
    BigInt c = static_cast<BigInt>(100500);
    String d = static_cast<String>("Stepik"); // <-
    Number * e = static_cast<Number *>(&с);
    BigInt * f = static_cast<BigInt *>(e); // <-
    void * g = static_cast<void *>(f);
    BigInt * h = static_cast<BigInt *>(g); // <-
    
    return 0;
}

