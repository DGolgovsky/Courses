#include <map>
#include <iostream>

using std::map;
using std::string;
using std::cout;
using std::cin;

typedef unsigned int uint;

map<char, uint> char_counter(const string& word)
{
    map<char, uint> char_count;
    uint word_size = word.size();
    for (uint i = 0; i < word_size; ++i) {
        ++char_count[word[i]];
    }
    return char_count;
}

int main(void)
{
    uint num_pair = 0;
	cout << "Check words pair is anagram.\n";
    std::cout << "Enter count of pairs: ";
    while (!(cin >> num_pair)) {
        std::cout << "Wrong number. Enter correct value: ";
    }
    map<string, string> pairs;
    { // Scope of filling map
        string key, value;
        for (uint i = 0; i < num_pair; ++i) {
            cout << "Enter [key value] for " << i + 1 << " pair: ";
            cin >> key >> value;
            pairs[key] = value;
        }
    }
    string result = "";
	cout << "> Result output:\n";
    for (const auto& [key, val] : pairs) {
        result = "not anagram.";
        if (char_counter(key) == char_counter(val))
            result = "is anagram.";
        cout << "Pair[" << key << ", " << val << "] "
                 << result << "\n";
    }

    return 0;
}
