/*
 * Напишите на языке C/C++ программу, определяющую номер треугольного числа
 * (см. также последовательность A000217 в «Энциклопедии целочисленных
 * последовательностей»).
 *
 * Примечание: число 0 (ноль) не считается принадлежащим ряду, который
 * считается начинающимся с единицы: 1, 3, 6, 10, 15, 21, 28, ... ﻿
 *
 * Вход: одно целое (возможно, со знаком «плюс» и символом «перевод строки»
 * \n) число в диапазоне от 1 до 9'223'372'036'854'775'807.
 *
 * Выход: порядковый номер поданного на вход числа в последовательности
 * треугольных чисел или 0 (ноль), если такого числа в последовательности
 * нет. Символ 0 (ноль) должен выдаваться и во всех случаях подачи на вход
 * некорректных (отрицательных и лежащих вне допустимого диапазона
 * положительных числовых, а также символьных / строковых) данных.
 *
 * Sample Input:
 * 10
 * Sample Output:
 * 4
 */

#include <iostream>
#include <cstdint>
#include <string>
#include <errno.h>

using namespace std;

#define MAX 9223372036854775807

bool ReadA(int64_t &a)
{
    std::string::size_type end = 0;
    std::string str;

    std::cin >> str;
    std::size_t found = str.find_first_not_of("+\n0123456789");
    if (found != std::string::npos)
        return false;
    else
        a = stoull(str, NULL, 0);
    long long value = 0;
    if (!(value = std::stoll(str, &end, 10)) || errno)
        return false;
    std::string s = to_string(value);
    if (a <= 0 || a > MAX)
        return false;
    else
        return true;
}

int main(void)
{
    int64_t a;
    int64_t b = 0;

    if (!ReadA(a)) {
        std::cout << 0;
        std::cout << std::endl;
        return 0;
    }
    
    for (; a > 0; ++b)
        a -= b;
    std::cout << (a ? 0 : b - 1);
    std::cout << std::endl;
    
    return 0;
}

