#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define NUM 10

int main()
{
    srand(time(NULL));
    int numbers[NUM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i, j;
    do
    {
        i = rand() % 10;
        j = rand() % 10;
    } while (i == j);
    printf("%d | %d \n%d | %d",i,numbers[i],j,numbers[j]);


}