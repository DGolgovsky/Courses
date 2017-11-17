using OtherType = void (*)(double) // C++11
typedef void (*OtherType)(double)  // C++03

typedef int * (Class::*Foo)(int, double) const;
using Foo = int * (Class::*)(int, double) const;
