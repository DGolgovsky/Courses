#include <string.h>
#include <stdio.h>

int stringStat(const char *string, size_t multiplier, int *count)
{
    *count = *count + 1;
	return strlen(string) * multiplier;
}

int main()
{
    int num = 0;
    int link = 5;
    num = stringStat("ASSHOLE\0", 2, &link);
    printf("%d, %d\n", num, link);

    return 0;
}
