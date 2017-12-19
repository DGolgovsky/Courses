/*
 * Слабый указатель.
 * Является "ручным" средством борьбы с циклическими ссылками.
 * Имеет метод lock, который возвращает "сильный" указатель std::shared_ptr.
 *
 * std::shared_ptr<Foo> PFoo(new Foo());
 * std::weak_ptr<Foo> WeakPFoo = PFoo;
 * {
 *    std::shared_ptr<Foo> LocalPFoo = WeakPFoo.lock();
 *    // Тут работа с LocalPFoo.
 * } // Тут LocalPFoo уничтожается.
 *
 * Документация: http://www.cplusplus.com/reference/memory/weak_ptr/
 */

// std::weak_ptr // For cycled pointers
/* Used when:
 * sp1 -> sp2
 * sp2 -> sp1
 */

std::shared_ptr<int> sp1(new int(5));

std::weak_ptr<int> wp1 = sp1;
{
    // Return ptr to obj if exist, else nullptr
    std::shared_ptr<int> sp2 = wp1.lock();
    if (sp2) {
        // ...
    }    
}
sp1.reset();
std::sgared_ptr<int> sp3 = wp1.lock(); // sp3 -> nullptr
if (sp3) {
    // ... Not executed
}
