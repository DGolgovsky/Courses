/*
 * Напишите функцию apply, которая принимает некоторую
 * функцию / функциональный объект, а так же аргументы для вызова этого
 * объекта, и вызывает его, используя perfect forwarding.
 *
 * Пример:
 * auto fun = [](std::string a, std::string const& b) { return a += b; };
 * std::string s("world!");
 * // s передаётся по lvalue ссылке,
 * // а временный объект по rvalue ссылке
 * s = apply(fun, std::string("Hello, "), s);
 *
 * Примечание: гарантируется, что количество аргументов, переданных в
 * apply, совпадает с количеством аргументов у функции/функционального
 * объекта. При этом у функции может быть произвольное число аргументов.
 *
 * Hint: в данном задании нужно использовать новый синтаксис
 * определения функций.
 */

#include <utility> // для std::move и std::forward

// реализация функции apply
template<typename T, typename ...Args>
auto apply (T fun, Args&&...args )
    -> decltype(fun(std::forward<Args>(args)...))
{
    return fun(std::forward<Args>(args)...);
}
