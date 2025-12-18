#include <stdio.h>
int main()
{
    int i, n, sum;
    printf("请输入一个正整数n: ");
    scanf("%d", &n);
    sum = 0;
    i = 1;//计数器的作用
    while(i <= n)
    {
        sum += i;
        i++;
    }
    printf("1到%d的和为: %d\n", n, sum);
    return 0;
}
//冷知识：可以使用等差数列求和公式计算1到n的和，公式为n*(n+1)/2