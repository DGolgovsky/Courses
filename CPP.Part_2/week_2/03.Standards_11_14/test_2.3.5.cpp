/*
 * Напишите constexpr бинарные операторы +, - и * (скалярное произведение) для структуры Point.
 *
 * Пример использования:
 * constexpr size_t size = static_cast<size_t>(Point(2,4) * Point(4,3));
 * int m[size]; // массив из 20 элементов
*/

// определение структуры Point уже подключено
/* struct Point
{
    constexpr Point(double x, double y) 
        : x(x), y(y) 
    {}

    double x = 0;
    double y = 0;
};
*/

constexpr Point operator+(const Point& a, const Point& b)
{
    return { a.x + b.x, a.y + b.y };
}

constexpr Point operator-(const Point& a, const Point& b)
{
    return { a.x - b.x, a.y - b.y };
}

constexpr double operator*(const Point& a, const Point& b)
{
    return a.x * b.x + a.y * b.y;
}
