/*
 * Определите класс Quantity, которые хранит вещественное число
 * и его размерность в системе СИ
 * (размерность хранится как список IntList длины 7).
 * Для этого класса нужно определить операторы сложения,
 * вычитания, умножения и деления.
 */

#include <iostream>

/* IntList */
template<int ... Ints> struct IntList;
template<int H, int ... T> struct IntList<H, T...>
{
    static int const Head = H;
    using Tail = IntList<T...>;
};
template<> struct IntList<> {};
/* IntList */

/* Zip */
template<typename TL1, typename TL2, template<int, int> class TMF>
struct Zip;
template<int ... Values1, int ... Values2, template<int, int> class TMF>
struct Zip<IntList<Values1...>, IntList<Values2...>, TMF>
{ using type = IntList<TMF<Values1, Values2>::value...>; };
/* Zip */

/* Auxiliary structs*/
template<int a, int b> struct Plus
{ static int const value = a + b; };
template<int a, int b> struct Minus
{ static int const value = a - b; };
/* Auxiliary structs*/

/* Quantity */
template <typename IL>
struct Quantity
{
public:
    Quantity() {}
    explicit Quantity(double value)
            :value_(value)
    { }

    double value() const { return value_; }

    Quantity<IL> operator+(const Quantity<IL> &rhs) const { return  Quantity<IL>(this->value_+rhs.value_);}
    Quantity<IL> operator-(const Quantity<IL> &rhs) const { return  Quantity<IL>(this->value_-rhs.value_);}
    Quantity<IL> operator*(double d) const { return  Quantity<IL>(this->value_*d);}
    Quantity<IL> operator/(double d) const { return  Quantity<IL>(this->value_/d);}

    template <typename IL2>
    Quantity<typename Zip<IL, IL2, Plus>::type> operator*(const Quantity<IL2> &rhs) const
    {
        return Quantity<typename Zip<IL, IL2, Plus>::type>(this->value_*rhs.value());
    };

    template <typename IL2>
    Quantity<typename Zip<IL, IL2, Minus>::type> operator/(const Quantity<IL2> &rhs) const
    {
        return Quantity<typename Zip<IL, IL2, Minus>::type>(this->value_/rhs.value());
    };

private:
    double value_;
};
/* Quantity */

// шаблон Dimension из условия уже определён
template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

using NumberQ   = Quantity<Dimension<>>;           // число без размерности
using LengthQ   = Quantity<Dimension<1>>;          // метры
using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах

int main()
{
    LengthQ   l{30000};      // 30 км
    TimeQ     t{10 * 60};    // 10 минут

    // вычисление скорости
    VelocityQ v = l / t;     // результат типа VelocityQ, 50 м/с

    AccelQ    a{9.8};        // ускорение свободного падения
    MassQ     m{80};         // 80 кг

    // сила притяжения, которая действует на тело массой 80 кг
    ForceQ    f = m * a;     // результат типа ForceQ

    /* For check results used gdb */

    return 0;
}
