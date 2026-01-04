#include <stdio.h>
int main()
{
    int i, j;
    scanf("%d %d", &i, &j);
    for (int m = 0; m < i; m = m + 1)
    {
        for (int n = 0; n < j; n = n + 1)
        {
            printf("*");
        }
        printf("\n");
    }
}