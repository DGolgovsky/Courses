/*
 * Владеющий указатель, то есть это значит, что на один объект указывает
 * ровно один указатель. Как только указатель уничтожается
 * (например, мы выходим за область видимости), для объекта вызывается
 * delete. Так же мы можем освободить указатель с помощью
 * вызова метода reset.
 *
 * std::unique_ptr<Foo> PFoo1(new Foo());
 * std::unique_ptr<Foo> PFoo2;
 *
 * PFoo2 = PFoo1; // Нельзя! Синтаксическая ошибка!
 * PFoo2 = std::move(PFoo1);
 * // Правильно! Теперь на объект указывает PFoo2,
 * // а PFoo1 не указывает никуда.
 * PFoo2.reset(); // Тут объект уничтожается.
 *
 * Документация: http://www.cplusplus.com/reference/memory/unique_ptr/
 */

// Since C++11
std::unique_ptr<Foo> sp1(new Foo());
std::unique_ptr<Foo> sp2;

// sp2 = sp1; // Compiletime error

sp2 = std::move(sp1); // sp1 -> nullptr

sp2.reset(); // sp2 -> nullptr
sp2.reset(); // No errors

sp1.reset(); // No errors
