#include <stdio.h>

int main()
{
    int m = 0;
    int i;
    scanf("%d", &i);
    while (m < i)
    {
        printf("*");
        m = m + 1;
    }
    return 0;
}