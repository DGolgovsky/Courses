#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr)   __builtin_expect(!!(expr), 1)

void foo();
void bar();

int main()
{
    int a;

    srand(time(NULL));
    a = rand() % 10;

    if (unlikely(a > 8)) // false in 90%
        foo();
    else
        bar;

    return 0;
}
