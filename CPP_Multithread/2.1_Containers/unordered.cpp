/*
 * Появились в C++11. Имеется четыре контейнера:
 * std::unordered_set,
 * std::unordered_multiset,
 * std::unordered_map,
 * std::unordered_multimap.
 *
 * Эти контейнеры реализованы с помощью хэш-таблиц,
 * способ разрешения коллизий - метод цепочек.
 * Подробнее на английской википедии:
 * https://en.wikipedia.org/wiki/Hash_table
 *
 * Документация:
 * http://www.cplusplus.com/reference/unordered_set/unordered_set/
 * http://www.cplusplus.com/reference/unordered_set/unordered_multiset/
 * http://www.cplusplus.com/reference/unordered_map/unordered_map/
 * http://www.cplusplus.com/reference/unordered_map/unordered_multimap/
 */

int main()
{
    // HASH-tables
    std::unordered_set<std::string> us;

    // hash: std::string -> unsigned int [0, 255]
    //
    //   0 |_______| -> [str] -> [str] -> [str] -> 0
    //   1 |_______|
    //   .
    //   .
    //   .
    // 254 |_______|
    // 255 |_______|

    /*
    std::unordered_set
    std::unordered_multiset
    std::unordered_map
    std::unordered_multimap
    */
}
