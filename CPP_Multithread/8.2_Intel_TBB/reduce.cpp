// prototype
float SerialSumFoo(float a[], size_t n)
{
    float sum = 0;
    for (size_t i = 0; i != n; ++i)
        sum += Foo(a[i]);
    return sum;
}

// parallel
class SumFoo
{
private:
    float *my_a;

public:
    float my_sum;
    void operator()(const tbb::blocked_range<size_t> &r) {
        float *a = my_a;
        float sum = my_sum;
        size_t end = r.end();
        for (size_t i = r.begin(); i != r.end(); ++i) {
            sum += Foo(a[i]);
        }
        my_sum = sum;
    }
    SumFoo(SumFoo &x, split)
        : my_a(x.my_a)
        , my_sum(0)
    { }
    void join(const SumFoo &y) {
        my_sum += y.my_sum;
    }
    SumFoo(float a[])
        : my_a(a)
        , my_sum(0)
    { }
};

float ParallelSumFoo(const float a[], size_t n)
{
    SumFoo sf(a);
    tbb::parallel_reduce(tbb::blocked_range<size_t>(0, n), sf);
    return sf.my_sum;
}

