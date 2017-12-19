/*
 * Указатель со счетчиком ссылок.
 * Допускает совместное владение объектом,
 * то есть много указателей может указывать на один объект.
 * Объект уничтожается с потерей последнего указателя на него
 * (когда счетчик ссылок станет равным нулю). Метод reset тоже существует.
 *
 * std::shared_ptr<Foo> PFoo1(new Foo());
 * std::shared_ptr<Foo> PFoo2;
 *
 * PFoo2 = PFoo1; // Можно! Теперь ОБА указателя указывают на один объект.
 *
 * PFoo1.reset();
 * PFoo2.reset(); // Тут объект уничтожается.
 *
 * Документация: http://www.cplusplus.com/reference/memory/shared_ptr/
 */

std::shared_ptr<Foo> pFoo(new Foo());
std::shared_ptr<Foo> pFoo2;

pFoo2 = pFoo;

pFoo.reset(); // Object still alive

pFoo2.reset(); // Object destroyed
