/*
 * Предположим, что вам даётся два указателя на объект некоторого сложного полиморфного класса,
 * который использует множественное наследование.
 * Оба указателя имеют один и тот же тип, но могут ссылаться на разные однотипные базы внутри одного объекта.
 *
 * Напишите шаблонную функцию, которая по двум однотипным указателям проверяет,
 * указывают ли они на один объект.
 */

// возвращает true, если p и q указывают на один и тот же объект
template<class T>
bool isSameObject(T const * p, T const * q)
{
    return (dynamic_cast<void const *>(p) == dynamic_cast<void const *>(q));
}
