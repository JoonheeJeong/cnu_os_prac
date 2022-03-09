#include <stdio.h>

int main()
{
    int x = 160;
    int y = 10;

    while (x > y) {
	x >>= 1;
	y++;
    }

    printf("x=%d, y=%d\n", x, y);

    return 0;
}
