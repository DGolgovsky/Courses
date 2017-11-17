#include <iostream>
#include <vector>
#include <iterator> // заголовочный файл итераторов

using namespace std;
 
int main()
{
    vector<int> array1; // создаем пустой вектор
    // добавляем в конец вектора array1 элементы 4, 3, 1
    array1.insert(array1.end(), 4);
    array1.insert(array1.end(), 3);
    array1.insert(array1.end(), 1);
    // вывод на экран элементов вектора
    copy( array1.begin(),   // итератор начала массива
          array1.end(),     // итератор конца массива
          ostream_iterator<int>(cout," ")   //итератор потока вывода
        );
    return 0;
}
