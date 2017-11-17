char * (*func(int, int))(int, int, int*, float);

// Analog 
typedef char* (*MyFunction)(int, int, int*, float);
MyFunction func(int, int);

// ComplexFunction
// C-style
typedef int* (*(*ComplexFunction)(int, int (*)(double)))(char const *);

// Human readable
typedef int* (*Ret_f)(char const *);
typedef Ret_f (*ComplexFunction)(int, int (*)(double));
