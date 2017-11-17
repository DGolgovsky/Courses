/*
 * Хранит отображение как хеш-таблицу
 * Добавление, удаление и поиск работают за O(1) в среднем
 *
 * equal_range, reserve, operator[], at
 */

#include <unordered_map>

std::unordered_map<std::string, int> phonebook;
phonebook.emplace("Marge", 2128506);
phonebook.emplace("Lisa",  2128507);
phonebook.emplace("Bart",  2128507);
// std::unordered_map<string,int>::iterator
auto it = phonebook.find("Maggie"); // <- phonebook.end()
if (it != phonebook.end())
    std::cout << "Maggie: " << it->second << '\n';

std::unordered_multimap<std::string, int> phonebook;
phonebook.emplace("Homer",  2128506);
phonebook.emplace("Homer",  5552368);

auto it = phonebook.find("Marge");
if (it != phonebook.end())
    it->second = 5550123; // if exist
else
    phonebook.emplace("Marge", 5550123); // if not exist
// OR
phonebook["Marge"] = 5550123;

/*
 * Метод operator[]:
 * 1. работает только с неконстантным map
 * 2. требует наличие у T конструктора по умолчанию
 * 3. работает за O(log n)
 * Метод at:
 * 1. генерирует ошибку вроемени выполнения, если ключ отсутствует
 * 2. работает за O(log n)
 */
