#include <stdio.h>
 
int main()
{
    int num;
    printf("Enter the number: ");
    scanf("%d", &num);

    int result = 1;
    for (int i = 2; i <= num; i++)
	result *= i;

    printf("The factorial of %d is %d\n", num, result);

    return 0;
}
     

