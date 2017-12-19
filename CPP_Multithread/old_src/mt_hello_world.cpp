//export OMP_NUM_THREADS = 4
#include <iostream>

int main(int argc, char ** argv)
{
#pragma omp parallel num_threads(4)
//#pragma omp parallel shared(A,B,C) or private(i,n)
    //omp_set_num_threads(4)
    {
        std::cout << "Hello, world!" << std::endl;
    }
#pragma omp parallel for redaction(+:sum)
    {
        for (int i = 0; i < 10000000; ++i) {
            //sum = sum + f(i);
            if (!i%2)
                std::cout << i;
        }
    }
    return 0;
}
