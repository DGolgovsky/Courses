/*
 * Хранит упорядоченное отображение (как дерево поиска по ключу)
 * Добавление, удаление и поиск работают за O(log n)
 *
 * typedef std::pair<const Key, T> value_type;
 *
 * lower_bound, upper_bound, equal_range
 * operator[], at
 * */

#include <map>

std::map<std::string, int> phonebook;
phonebook.emplace("Marge", 2128506);
phonebook.emplace("Lisa",  2128507);
phonebook.emplace("Bart",  2128507);
// std::map<string,int>::terator
auto it = phonebook.find("Maggie"); // <- phonebook.end()
if (it != phonebook.end())
    std::cout << "Maggie: " << it->second << '\n';

std::multimap<std::string, int> phonebook;
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
