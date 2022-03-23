#include "calc_func.h"

int main()
{
    int a, b;
    printf("----Simple Calculator---\n"
	   "input a: ");
    scanf("%d", &a);
    printf("input b: ");
    scanf("%d", &b);

    printf("\n----Result----\n");
    add(a, b);
    sub(a, b);
    mul(a, b);
    div(a, b);

    return 0;
}
