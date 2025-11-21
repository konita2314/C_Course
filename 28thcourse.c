#include <stdio.h>
int main()
{
    int score[5];
    int total = 0;
    int i;
    printf("Input the 5 data\n");
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &score[i]);
        total = total + score[i];
    }
    printf("The total is %f\n", total / 5.0);
}