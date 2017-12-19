/*
 * Тут задача очень простая.
 * Вам нужно создать умный указатель на объект класса std::string.
 * Он должен иметь защиту от разыменования NULL - при попытке это сделать
 * он должен конструировать внутри себя пустую строку.
 *
 * Следующий код должен работать:
 * std::string s1 = "Hello, world!";
 *
 * StringPointer sp1(&s1);
 * StringPointer sp2(NULL);
 *
 * std::cout << sp1->length() << std::endl;
 * std::cout << *sp1 << std::endl;
 * std::cout << sp2->length() << std::endl;
 * std::cout << *sp2 << std::endl;
 *
 * N.B. Так как ваш указатель при определенных случаях может
 * конструировать внутри себя пустую строку,
 * не забудьте позаботиться об освобождении памяти в деструкторе.
 * Система не проверяет корректность работы в памятью,
 * так что это остается на вашу совесть :)
 */

class StringPointer {
public:
    StringPointer(std::string* ptr) : ptr_(ptr ? ptr : new std::string()), owner(ptr == nullptr)  {}
    ~StringPointer() { if (owner) { delete ptr_; } }
    
    StringPointer(const StringPointer& other) = delete;
    StringPointer& operator=(const StringPointer& other) = delete;

    std::string& operator*() { return *ptr_; }
    std::string* operator->() { return ptr_; }

private:
    std::string* ptr_;
    bool owner;
};
