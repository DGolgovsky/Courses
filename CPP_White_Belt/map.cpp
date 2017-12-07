#include <iostream>
#include <vector>
#include <map>

using namespace std;

void printMap(const map<string, int>& m)
{
    cout << "Size: " << m.size() << endl;
    for (const auto& item : m) {
        cout << item.first << ": " << item.second << endl;
    }
}

int main()
{
    vector<string> words = {"one", "two", "three"};
    map<string, int> counters;
    for (const string& word : words) {
        /*
         * Метод добавляет отсутствующие ключи автоматически со значением
         * 0 по умолчанию.
         * Если ключ уже имеется, то инкрементирует его
         */
        ++counters[word];
    }

    map<char, vector<string>> grouped_words;
    for (const string& word : words) {
        grouped_words[word[0]].push_back(word);
    }
    for (const auto& item : grouped_words) {
        cout << item.first << ": ";
        for (const string& word : item.second) {
            cout << word << " ";
        }
        cout << endl;
    }
    return 0;
}
