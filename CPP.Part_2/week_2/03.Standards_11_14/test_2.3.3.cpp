/*
 * Напишите шаблонную функцию to_pair, которая принимает
 * произвольный std::tuple и два индекса внутри и
 * возвращает std::pair, содержащий элементы переданного std::tuple с соответствующими индексами.
 * Пример:
 * auto t = std::make_tuple(0, 3.5, "Hello");
 * std::pair<double, char const *> p = to_pair<1,2>(t);
 * // p содержит 3.5 и "Hello"
 * Замечание: реализация должна работать в рамках стандарта C++11.
 */

#include <tuple>
#include <utility>  // std::forward
#include <iostream> // std::cout

namespace _detail_
{
    // Главная роль здесь у шаблона класса iterate_tuple.

    // Первый параметр шаблона класса iterate_tuple имеет тип int (index).
    // Значение этого параметра используется функцией get,
    // которая "достает" из кортежа элемент по указанной позиции.

    // Мы рекурсивно сдвигаем позицию (уменьшаем index на 1) и таким образом
    // перемещаемся по кортежу.

    // Когда значение индекса становится равно 0, рекурсия завершается,
    // благодаря частичной специализации для индекса равного 0.

    // При этом есть особый случай, когда индекс равен -1. Он соответствует
    // ситуации, когда кортеж не содержит ни одного элемента.

    template<int index, typename Callback, typename... Args>
    struct iterate_tuple {
        static void next(std::tuple<Args...>& t, Callback callback) {
            // Уменьшаем позицию и рекурсивно вызываем этот же метод
            iterate_tuple<index - 1, Callback, Args...>::next(t, callback);

	    // Вызываем обработчик и передаем ему позицию и значение элемента
	    callback(index, std::get<index>(t));
	}
    };

    // Частичная специализация для индекса 0 (завершает рекурсию)
    template<typename Callback, typename... Args>
    struct iterate_tuple<0, Callback, Args...> {
        static void next(std::tuple<Args...>& t, Callback callback) {
            callback(0, std::get<0>(t));
        }
    };

    // Частичная специализация для индекса -1 (пустой кортеж)
    template<typename Callback, typename... Args>
    struct iterate_tuple<-1, Callback, Args...> {
        static void next(std::tuple<Args...>& t, Callback callback) {
            // ничего не делаем
        }
    };
}

// "Волшебный" for_each для обхода элементов кортежа (compile time!):
template<typename Callback, typename... Args>
void for_each(std::tuple<Args...>& t, Callback callback)
{
    // Размер кортежа
    int const t_size = std::tuple_size<std::tuple<Args...>>::value;

    // Запускаем рекурсивный обход элементов кортежа во время компиляции
    _detail_::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
}

// Код функции for_each опущен для простоты примера
// (его лучше вынести в отдельный файл *.h)
struct callback
{
    template<typename T>
    void operator()(int index, T&& t) // index - это позиция элемента в кортеже
    {                                 // t - значение элемента
        std::cout << index << '=' << t << std::endl;
    }
};

template<size_t I1,
         size_t I2,
         typename... Args,
         typename A = typename std::tuple_element<I1, std::tuple<Args...>>::type,
         typename B = typename std::tuple_element<I2, std::tuple<Args...>>::type >
std::pair<A, B> to_pair(std::tuple<Args...>& tuple_)
{
   // Значения аргументов функции внутри кортежа
   //auto tuple_ = std::make_tuple(std::forward<Args>(args)...);

   // Обход элементов кортежа и вызвов обработчика
   //for_each(tuple_, callback());
   auto pair_ = std::make_pair(std::get<I1>(tuple_), std::get<I2>(tuple_));
   return pair_;
}

int main()
{
    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1,2>(t); 
    // p содержит 3.5 и "Hello"
    std::cout << p.first << ", " << p.second << '\n';
    return 0;
}

