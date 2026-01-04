#include <stdio.h>
#include <string.h>
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j > 0; j--)
        {
            if(j>i+1)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }
}