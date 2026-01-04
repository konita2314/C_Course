#include <stdio.h>
int main(void)
{
    int a;
    int b = 0;
    scanf("%d", &a);
    while (b <= a)
    {
        printf("*");
        b = b + 1;
    }
    return 0;
}
/*
for (b = 0; b <= a; b++)
{
    printf("*");
}
*/