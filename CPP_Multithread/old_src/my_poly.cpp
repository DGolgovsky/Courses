#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>

int main()
{
    std::string str;
    std::cin >> str;
    int strSize = str.size();
//  How many monomials has the polynomial?
    int k = 1;
    for (int i = 1; i < strSize; ++i)
        if (str[i] == '+' || str[i] == '-')
            k++;
    int monoms = k;

//  Signs "+" are necessary for the string parsing 
    if (isdigit(str[0]))
        str.insert(0, "+");
    if (str[0] == 'x')
        str.insert(0, "+");
    str.append("+");
    strSize = str.size();

//  Extracting the monomials as monomStr
    k = 0;
    int j = 0;
    std::string monomStr[monoms];
    for (int i = 1; i < monomStr[i].size(); ++i)
        if (str[i] == '+' || str[i] == '-') {
            monomStr[k++] = str.substr(j, i - j);
            j = i;
        }

    for (int i = 0; i != ; ++i) {
        std::cout << monomStr[i] << "\n";
    }
    return 0;
}

