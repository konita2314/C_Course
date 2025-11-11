#include <stdio.h>
int main()
{
    int a, i, j;
    printf("Please input a natural number:");
    scanf("%d",&a);
    for (i = 0;i < a;i++)
    {
        for (j = 0;j < a;j++)
        {
            printf("[142857]");
        }
        printf("\n");
    }
    return 0;
}