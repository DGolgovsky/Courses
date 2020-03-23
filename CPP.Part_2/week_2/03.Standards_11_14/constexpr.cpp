constexpr double accOfGravity = 9.8;
constexpr double moonGravity = accOfGravity / 6;

constexpr int pow(int x, int k)
{
    return k == 0 ? 1 : x * pow(x, k - 1);
}

int data[pow(3, 5)] = {};

struct Point
{
    double x, y;
    constexpr Point(double x = 0, double y = 0)
        : x(x), y(y) {}
    constexpr double getX() const { return x; }
    constexpr double getY() const { return y; }
};
constexpr Point p(moonGravity, accOfGravity);
constexpr auto x = p.getX();

