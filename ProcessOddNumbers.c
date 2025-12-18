#include <stdio.h>

int main(void)
{
    int a,b;
    scanf("%d", &a);
    b = a % 2;
    if (b == 0)
        printf("%d是偶数\n", a);
    else
        printf("%d是奇数\n", a);
}