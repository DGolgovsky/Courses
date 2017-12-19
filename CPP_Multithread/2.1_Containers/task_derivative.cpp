/*
 * Посмотрим, насколько хорошо вы умеете обращаться с контейнерами!?
 *
 * Задача простая - найти производную многочлена.
 * Многочлен может быть большой, но только с неотрицательными целыми
 * степенями и целыми коэффициентами. Подумайте, каким образом его лучше
 * представить в памяти? Вывод должен быть без пробелов и в порядке
 * убывания степеней, хотя ввод этому правилу может не удовлетворять.
 * Также на ввод может быть подан многочлен с неприведенными слагаемыми.
 *
 * Для этой задачи существует 10 тестов, созданных вручную
 * (3 из них вы можете увидеть ниже)
 * и 90 тестов, созданных автоматически случайным образом.
 *
 * Sample Input 1:
 * x^2+x
 * Sample Output 1:
 * 2*x+1
 *
 * Sample Input 2:
 * 2*x^100+100*x^2
 * Sample Output 2:
 * 200*x^99+200*x
 *
 * Sample Input 3:
 * x^10000+x+1
 * Sample Output 3:
 * 10000*x^9999+1
 *
 * Sample Input 4:
 * -x^2-x^3
 *  Sample Output 4:
 *  -3*x^2-2*x
 *
 *  Sample Input 5:
 *  x+x+x+x+x+x+x+x+x+x
 *  Sample Output 5:
 *  10
 */

#include <regex>
#include <iostream>
#include <sstream>
#include <map>
#include <string>

using namespace std;
 
std::string derivative(std::string polynomial)
{
    std::string s = polynomial;
    // Ключ - степень икса, значение - коеффициент при икс
    std::map<int, int> poly;
    std::map<int, int> dxpoly;
    if (polynomial[0] != '-')
        s = '+' + s;
    
    const regex r("([+|-]\\d+)([\\*]x([\\^](\\d+))?)?");
    const regex rr("([+|-])x");
    const string fmt("$011*x");
    s = regex_replace(s, rr, fmt);
    
    for(sregex_iterator i(s.begin(), s.end(), r), end; i != end; ++i) {
        //cout << " " << (*i)[0] << "\t" << (*i)[1] << "\t" << (*i)[2] << "\t" << (*i)[3] << "\t" << (*i)[4] << endl;
        // Только число. Коеффициент при x^0
        if ((*i)[2] == "") {
            int an = atoi((*i)[1].str().c_str());
            poly[0] += an;
        // x^1
        } else if ((*i)[2] == "*x") {
            int an = atoi((*i)[1].str().c_str());
            poly[1] += an;
        } else {
            int an = atoi((*i)[1].str().c_str());
            int xn = atoi((*i)[4].str().c_str());
            poly[xn] += an;
        }
    }
    // Derivate
    for (auto it = poly.begin(); it != poly.end(); ++it) {
        dxpoly[it->first - 1] = it->second * it->first;
    }
    // Grap result
    stringstream ss;
    for (auto it = dxpoly.rbegin(); it != dxpoly.rend(); ++it) {
        if (it->first < 0)
            continue;
        if (it->first == 0) {
            ss << showpos << it->second;
        } else if (it->first == 1) {
            if (abs(it->second) == 1)
                ss << (it->second > 0 ? "+x" : "-x");
            else
                ss << showpos << it->second << "*x";
        } else {
            if (abs(it->second) == 1)
                ss << (it->second > 0 ? "+x" : "-x")
                   << "^" << noshowpos << it->first;
            else
                ss << showpos << it->second << "*x^"
                   << noshowpos << it->first;
        }
    }
 
    string result = ss.str();
    if (result.size() == 0)
        return "0";
    if (result[0] == '+')
        return result.substr(1);
 
    return result;
}
