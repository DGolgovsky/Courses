// parallel_for
// #omp parallel for
void SerialApplyFoo(float a[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        Foo(a[n]);
}

//#1
class ApplyFoo
{
    float *my_a;
public:
    void operator()(const tbb:blocked_range<size_t> &r) {
        float *a = my_a;
        for (size_t i = r.begin(); i != r.end(); ++i) {
            Foo(a[i]);
        }
    }
    ApplyFoo(float a[]): my_a(a) { }
};

void ParallelApplyFoo(float a[], size_t n)
{
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n), ApplyFoo(a));
}

//#2
void ParallelApplyFoo(float a[], size_t n)
{
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
            [=](const tbb::blocked_range<size_t> &r) {
            for (size_t i = r.begin(); i != r.end(); ++i)
            Foo(a[i]);
            }
    );
}

//#blocks
tbb::parallel_for(tbb::blocked_range<size_t>(0, n, G),
        ApplyFoo(a),
        simple_partitioner());

