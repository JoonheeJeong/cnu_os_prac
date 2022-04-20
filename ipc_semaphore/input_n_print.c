#include <stdio.h>

#define BUF_SIZE 64

int main()
{
    char buf[BUF_SIZE];
    fgets(buf, BUF_SIZE, stdin);
    printf("input : %s", buf);
    return 0;
}
