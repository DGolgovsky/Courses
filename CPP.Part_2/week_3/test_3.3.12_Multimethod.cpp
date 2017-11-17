#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <utility>  
#include <functional>
 
// базовый класс фигуры (полиморфный)
struct Shape {virtual ~Shape() {}};
 
// прямоугольник
struct Rectangle : Shape { };
 
// треугольник
struct Triangle : Shape {};
 
// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b) {
    std::cout << "Called: is_intersect_r_r" << std::endl;
    return true;
}
 
// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b) {
    std::cout << "Called: is_intersect_r_t" << std::endl;
    return true;
}
 
// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
 
    using Fun   = std::function<Result(Base*, Base*)>;
    using Key   = std::pair<const char*, const char*>;
    using Val   = std::pair<Fun, bool>;
    using Store = std::map<Key, Val>;
    Store info;
 
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid 
    // f - это функция или функциональный объект
    // принимающий два указателя на Base 
    // и возвращающий значение типа Result
    void addImpl(const std::type_info& t1, const std::type_info& t2, Fun f)
    {
        Key key(std::type_index(t1).name(), std::type_index(t2).name());
        Val val(f, true);
        //std::cout << "1: " << key.first << ", " << key.second << '\n';
        //info.insert(std::make_pair(key, f));
        info[key] = val;
        if (Commutative) {
            Key key2(std::type_index(t2).name(), std::type_index(t1).name());
            Val val2(f, false);
            //std::cout << "2: "<< key2.first << ", " << key2.second << '\n';
            //info.insert(std::make_pair(key2, f));
            info[key2] = val2;
        }
    }
 
    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно 
        // проверить есть ли реализация для b и а
        Key key(typeid(*a).name(), typeid(*b).name());
        
        //std::cout << "3: "<< key.first << ", " << key.second << '\n';
        auto got = info.find(key);        
        if (got!=info.end()) return true;
        std::cout << "HasImpl: " << 0 << "\n";
        return false; 
    }
 
    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        Key key(typeid(*a).name(), typeid(*b).name());
        std::cout << "4: "<< key.first << ", " << key.second << '\n';
        auto got = info.find(key);
        auto t = (got->second).second;
        
        if (t) {
            std::cout << "ret (a,b)" << '\n';
            return (got->second).first(a,b);
        } else {
            std::cout << "ret (b,a)" << '\n';
            return (got->second).first(b,a);
        }        
    }
};
 
 
int main() {
    // мультиметод для наследников Shape
        // возращающий bool и являющийся коммутативным 
        Multimethod2<Shape, bool, true> is_intersect;
 
        // добавляем реализацию мультиметода для двух прямоугольников
        is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
 
        //// добавляем реализацию мультиметода для прямоугольника и треугольника
        is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);
        //is_intersect.addImpl(typeid(Triangle), typeid(Triangle), is_intersect_r_t);
 
        //// создаём две фигуры    
        Shape * s1 = new Triangle();
        Shape * s2 = new Rectangle();
        //Shape * s3 = new Triangle();
 
        //// проверяем, что реализация для s1 и s2 есть
        if (is_intersect.hasImpl(s1, s2))
        {
             // вызывается функция is_intersect_r_t(s2, s1)
             bool res = is_intersect.call(s1, s2);
             std::cout << "Method is found!\n";
 
             // Замечание: is_intersect_r_t ожидает,
             // что первым аргументом будет прямоугольник
             // а вторым треугольник, а здесь аргументы
             // передаются в обратном порядке. 
             // ваша реализация должна самостоятельно 
             // об этом позаботиться
        } else {
         std::cout << "Method is NOT found!\n"; 
        }
        if (is_intersect.hasImpl(s2, s2))
        {
             // вызывается функция is_intersect_r_t(s2, s1)
             bool res = is_intersect.call(s2, s2);
             std::cout << "Method is found!\n";
 
             // Замечание: is_intersect_r_t ожидает,
             // что первым аргументом будет прямоугольник
             // а вторым треугольник, а здесь аргументы
             // передаются в обратном порядке. 
             // ваша реализация должна самостоятельно 
             // об этом позаботиться
        } else {
         std::cout << "Method is NOT found!\n"; 
        }
        if (is_intersect.hasImpl(s1, s1))
        {
             // вызывается функция is_intersect_r_t(s2, s1)
             bool res = is_intersect.call(s1, s1);
             std::cout << "Method is found!\n";
 
             // Замечание: is_intersect_r_t ожидает,
             // что первым аргументом будет прямоугольник
             // а вторым треугольник, а здесь аргументы
             // передаются в обратном порядке. 
             // ваша реализация должна самостоятельно 
             // об этом позаботиться
        } else {
         std::cout << "Method is NOT found!\n"; 
        }

        return 0;
}
