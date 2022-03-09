#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int num;
    printf("Enter the number: ");
    scanf("%d", &num);

    double j;
    for(int i = 0; i < num; i++){
	j = i/3 + i;
	printf("j = %lf \n", j);
    }

    char *str = NULL;
    str = (char *)  malloc(10 * sizeof(char)); // must be added!
    strcpy(str, "Success!");
    printf("%s\n", str);

    return 0;
}

