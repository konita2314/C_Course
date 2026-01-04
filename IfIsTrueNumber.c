#include <stdio.h>
#include <stdlib.h>
int istruenumber(int num)
{
    long long int a;
    if (num < 2)
    {
        printf("Please input a (>=2)natural number!");
        return -1;
    }

    for (a = 2; a <= num - 1; a++)
    {
        if (num % a == 0)
        {
            printf("NO"); // 找到除了1以外的除数，不是质数
            return 1;
        }
    }

    // 循环结束都没找到除数，是质数
    printf("YES");
    return 0;
}
int main()
{
    int i;
    scanf("%d", &i);
    istruenumber(i);
}