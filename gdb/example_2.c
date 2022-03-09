#include <stdio.h>

int sum(int x, int y) { return x + y; }

int main()
{
    int x = 12;
    int y = 15;
    int z = sum(x, y);

    printf("result: %d\n", z);

    return 0;
}
