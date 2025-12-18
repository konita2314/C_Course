#include <stdio.h>

int main()
{
    int a, b, max;
    printf("请输入两个整数: ");
    scanf("%d %d", &a, &b);
    max = (a > b) ? a : b;//使用三元运算符求较大值,?:号前是条件表达式,为真时取?后面的值,为假时取:后面的值
    printf("较大值是: %d\n", max);
    return 0;
}