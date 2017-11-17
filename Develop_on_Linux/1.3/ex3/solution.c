#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int (*function)(int);

bool init_library(const char *lib_name,
                  const char *func_name)
{
    void *hdl = dlopen(lib_name, RTLD_LAZY);
    if (NULL == hdl)
        return false;

    function = (int (*)(int))dlsym(hdl, func_name);
    if (NULL == function)
        return false;

    return true;
}

int main(int argc, char ** argv)
{
    int result = 0;

    if (init_library(argv[1], argv[2]))
        result = function(atoi(argv[3]));
    else
        printf("Library was not loaded\n");

    printf("%d\n", result);

    return 0;
}
