char * (*func(int, int))(int, int, int*, float);

// Analog 
typedef char* (*MyFunction)(int, int, int*, float);
MyFunction func(int, int);

/*
 * При помощи typedef определите тип ComplexFunction, который является указателем на функцию,
 * которая принимает int и указатель на функцию, принимающую double и возвращающую int,
 * и возвращает указатель на функцию, которая принимает char const * и возвращает int *
 */

// ComplexFunction
// C-style
typedef int* (*(*ComplexFunction)(int, int (*)(double)))(char const *);

// Human readable
typedef int* (*Ret_f)(char const *);
typedef Ret_f (*ComplexFunction)(int, int (*)(double));
