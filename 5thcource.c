#include <stdio.h>
#include <limits.h>

int main(void) 
{
    printf("char类型范围: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("int类型范围: %d to %d\n", INT_MIN, INT_MAX);
    printf("short类型范围: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("long类型范围: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("long long类型范围: %lld to %lld\n\n", LLONG_MIN, LLONG_MAX);
    printf("现在开始验证输入输出:\n");
    // 验证int类型
    printf("请输入一个整数（现在是int类型）:\n");
    int a;
    scanf("%d", &a);
    printf("这个数是:%d\n", a);
    //可以看到，当输入的数超过int类型范围时，输出结果会变成负数。
    //比如输入3000000000，输出结果是-1294967296。
    //这是因为int类型在大多数系统上是32位的，范围是-2147483648到2147483647。
    //当输入的数超过这个范围时，会发生整数溢出，导致结果变成负数。

    // 验证long类型
    printf("请输入一个整数（现在是long int类型）:\n");
    long int b;
    scanf("%ld", &b);
    printf("这个数是:%ld\n", b);

    // 验证long long类型
    printf("请输入一个整数（现在是long long int类型）:\n");
    long long int c;
    scanf("%lld", &c);
    printf("这个数是:%lld\n", c);

    return 0;
}