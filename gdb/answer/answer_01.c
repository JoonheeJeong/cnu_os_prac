#include <stdio.h>

int main() {
    int array[5][5] = {
	{99, 22, 73 ,46, 12}, 
	{14, 85, 86, 58, 61},
	{95,  3, 78, 79, 49},
	{45, 96, 47, 81, 83},
	{82,  8, 12, 36, 27}
    };

    int m = 0;
    int n = 0;
    int k = 0;

    while(*(*(array + m) + n) != 61) {
	m = 1;
	n = 4;
    }

    printf("You just passed Path 1\n");

    while(*(*array + k) != 79) {
	k = 13;
    }

    printf("Success!\n");
	
    return 0;
}

