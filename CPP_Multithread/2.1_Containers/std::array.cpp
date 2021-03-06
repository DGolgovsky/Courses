/*
 * std::array - статический массив (C++11).
 * Является минимальной оболочкой над обычными массивами языка C.
 * Размер массива задается во время компиляции.
 * Память для элементов выделяется там, где объявлен массив
 * (в частности, если массив объявлен на стеке,
 * то и его элементы будут находиться на стеке).
 *
 * Документация: http://www.cplusplus.com/reference/array/array/
 */

#include <array>

int main()
{
    std::array<int, 16> a;
    // Don't have:
    // a.capacity()
    // insert, delete, pop_back, push_back
}
