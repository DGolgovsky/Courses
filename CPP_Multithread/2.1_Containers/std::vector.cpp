/*
 * std::vector - динамический массив. Может занимать
 * память "с запасом". Можно вставлять элементы в середину,
 * удалять из середины, изменять размер массива и размер
 * аллоцированной памяти в любое время.
 * Элементы массива всегда создаются на куче.
 *
 * Документация: http://www.cplusplus.com/reference/vector/vector/
 */

#include <vector>
#include <iostream>
#include <string>
#include <iterator> // заголовочный файл итераторов

using std::vector;

template<typename T>
void print(std::string &&msg, T &&str, bool endl = 1)
{
    std::cout << msg << " :: " << str;
    if (endl)
        std::cout << std::endl;
    else
        std::cout << ", ";
}

int main()
{
    vector<int> v(16, 0);

    print("v.size()", v.size());            // == 16
    print("v.capacity()", v.capacity());    // >= 16

    v.resize(32);           // v.size() == 32
    v.reserve(128);         // v.capacity() == 128

    vector<int>::iterator plc = v.begin();
    v.insert(plc+7, 23);
    v.erase(plc+1);

    v.push_back(42);        // insert to back
    v.pop_back();           // delete from back

    v[12] = 123;
    print("v[12]", v[12]);           // 123

    // C++03
    for (vector<int>::iterator it = v.begin();
         it != v.end(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;


    // C++11
    for (auto it = v.begin(); it != v.end(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;


    // C++03 :: Constant
    for (vector<int>::const_iterator it = v.cbegin();
         it != v.cend(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;

    // C++11 :: Reversed
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;

    // C++11 :: Const Reversed
    for (auto it = v.crbegin(); it != v.crend(); ++it) {
        print("", *it, 0);
    }
    std::cout << std::endl;

    vector<int> array1; // создаем пустой вектор
    // добавляем в конец вектора array1 элементы 4, 3, 1
    array1.insert(array1.end(), 4);
    array1.insert(array1.end(), 3);
    array1.insert(array1.end(), 1);
    // вывод на экран элементов вектора
    std::copy( array1.begin(),   // итератор начала массива
          array1.end(),     // итератор конца массива
          ostream_iterator<int>(std::cout, " ")   //итератор потока вывода
    );

    return 0;
}
