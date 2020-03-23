/*
 * По аналогии с функцией printf с предыдущего степа напишите функцию print_values
 * с переменным числом аргументов, которая для каждого аргумента выводит
 * его тип и значение в поток std::ostream, который ей передан в качестве первого аргумента.
 * Функция должна работать с произвольным числом аргументов.
 * Указание: для вывода имени типа нужно использовать std::type_info::name.
 *
 * Например, вызов функции
 * print_values(std::cout, 0, 3.5, "Hello");
 * должен вывести на стандартный вывод примерно следующее (таким будет вывод на g++).
 * i: 0
 * d: 3.5
 * PKc: Hello
 *
 * Примечание: в этой и следующих задачах на программирование будет использоваться стандарт C++11.
 * Если вы захотите решать задачи локально, то не забудьте включить поддержку стандарта C++11
 * в вашем компиляторе.
 * Например, в g++ и clang++ поддержка С++11 включается при помощи
 * следующего параметра командной строки: -std=c++11.
 *
 * Внимание: выводить нужно в поток os, а не в std::cout!
 */

#include <iostream>
#include <typeinfo>

/**
 * Another solution:
 *
 * template<typename Arg>
 * void print_values(std::ostream & os, const Arg & arg)
 * {
 *     os << typeid(arg).name() << ": " << arg << std::endl;
 * }
 *
 * template<typename ...Args>
 * void print_values(std::ostream & os, const Args & ...args)
 * {
 *     int values[] = {(print_values(os, args), 0)...};
 * }
 */

/**
 * C++17 solution
 *
 * #include <ostream>
 * #include <typeinfo>
 *
 * template <typename... Args>
 * void print_values(std::ostream & os, const Args&... args)
 * {
 *     ((os << typeid(args).name() << ": " << args << "\n"), ...);
 * }
 */

void print_values()
{ }

void print_values(std::ostream const &os)
{
    return;
}

template<typename VType, typename ... Args>
void print_values(std::ostream &os,
                  VType const &value,
                  Args const &... args)
{
    os << typeid(value).name() << ": "
       << value << '\n';
    print_values(os, args...);
}

int main()
{
    print_values(std::cout, 0, 3.5, "Hello");
    print_values(std::cout);
    //print_values();

    return 0;
}
