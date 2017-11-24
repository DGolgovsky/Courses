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
template<class L>
class Quantity
{
private:
    double val;
public:
    explicit Quantity(double val = 0)
            :val(val)
    { }
    double value() const noexcept {
        return val;
    }
    Quantity operator+(Quantity const& rhs) const noexcept {
        return Quantity(val + rhs.val);
    }
    Quantity operator-(Quantity const& rhs) const noexcept {
        return Quantity(val - rhs.val);
    }

    template<class B>
    Quantity<typename Zip<L, B, Plus>::type>
        operator*(Quantity<B> const& rhs) const noexcept {
        return Quantity<typename Zip<L, B, Plus>::type>(val * rhs.value());
    }
    Quantity operator*(double val) const noexcept {
        return Quantity<L>(this->val * val);
    }

    template<class B>
    Quantity<typename Zip<L, B, Minus>::type>
        operator/(Quantity<B> const& rhs) const noexcept {
        return Quantity<typename Zip<L, B, Minus>::type>(val / rhs.value());
    }
    Quantity operator/(double val) const noexcept {
        return Quantity<L>(this->val / val);
    }
};

template<class L>
Quantity<L> operator*(double val, Quantity<L> const& rhs) noexcept {
    return Quantity<L>(rhs.value() * val);
}

template<class L>
Quantity<typename Zip<IntList<0,0,0,0,0,0,0>, L, Minus>::type>
    operator/(double val, Quantity<L> const& rhs) noexcept {
    return Quantity<typename Zip<IntList<0, 0, 0, 0, 0, 0, 0>, L, Minus>::type>(val/rhs.value());
}
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
