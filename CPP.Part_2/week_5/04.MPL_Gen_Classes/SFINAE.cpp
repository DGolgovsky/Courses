/*
 * SFINAE - Substitution Failure Is Not An Error.
 * Ошибка при подстановке шаблонных параметров
 * не является сама по себе ошибкой
 */

// ожидает, что у типа Т определён
// вложенный тип value_type
template<class T>
void foo(typename T::value_type *v); // int doesn't have ::value_type

// работает с любым типом
template<class T>
void foo(T t); // <- used with foo<int>(0);

// при инстанциировании первой перегрузки
// происходит ошибка (у int нет value_type),
// но это не приводит к ошибке компиляции
foo<int>(0);
