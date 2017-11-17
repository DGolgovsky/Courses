/*
 * Напишите возвращающую bool шаблонную функцию compare, которая принимает
 * две константные ссылки на объекты одного типа и указатель на константный
 * метод этого типа без параметров, который в свою очередь возвращает
 * значение какого-то второго типа. Функция должна сравнивать объекты по
 * значениям, которые для них вернёт соответствующий метод, и возвращать
 * true, если значение для первого объекта оказалось меньше, чем для
 * второго.
 */

#include <iostream>
#include <string>

template class std::basic_string<char>;

/* С использованием alias template
 * template<typename T, typename U>
 * using Method_ptr = U (T::*)() const;
 *
 * template<typename T, typename U>
 * bool compare(const T& a, const T& b, Method_ptr<T, U> mptr)
 * {
 *   return (a.*mptr)() < (b.*mptr)();
 * }
 */

template<class T, typename RT>
bool compare(T const &a, T  const &b, RT (T::*mptr)() const)
{
    return (a.*mptr)() < (b.*mptr)();
}

int main()
{
    std::string s1("Elf");
    std::string s2("Archer");

    // Comaration strings by size
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false
    bool r3 = compare(s2, s2, &std::string::size); // ??
    bool r4 = compare(s2, s1, &std::string::size); // ??

    std::cout << "r1 = " << r1 << ", "
              << "r2 = " << r2 << ", "
              << "r3 = " << r3 << ", "
              << "r4 = " << r4 << '\n';

    return 0;
}

