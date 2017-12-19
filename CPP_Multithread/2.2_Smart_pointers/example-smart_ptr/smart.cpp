#include <iostream>

template <class T>
class SmartPointer
{
    private:
        T *pointer;
    public:
        SmartPointer(T *p): pointer(p) {}
        operator T*() {
            return pointer;
        }
        T *operator->() {
            if (!pointer) {
                pointer = new T();
                std::cerr << "Bad pointer!" << std::endl;
            }
            return pointer;
        }
        std::ptrdiff_t operator-(SmartPointer<T> p) {
            return pointer - p;
        }
        std::ptrdiff_t operator-(void *p) {
            return pointer - p;
        }
};

class foo
{
    private:
        int a, b;
    public:
        foo(): a(0), b(0) {}
        foo(int a, int b): a(a), b(b) {}
        int sum() {
            return a + b;
        }
};

int main(int argc, char **argv)
{
    SmartPointer<foo> sp(new foo(2, 2));
    SmartPointer<foo> sp(NULL); // Segmentation fault
    std::cout << sp->sum() << std::endl;

    return 0;
}

