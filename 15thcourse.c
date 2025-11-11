#include <stdio.h>
int main()
{
    int i, n, sum;
    printf("请输入一个正整数n: ");
    scanf("%d", &n);
    sum = 0;
    for(i = 1; i <= n; i++)//第一个参数初始化循环变量i，第二个参数是循环条件，第三个参数是每次循环后执行的操作
    {
        sum += i;
    }
    printf("1到%d的和为: %d\n", n, sum);
    return 0; 
}
//以上效果如果使用while语句实现
/*
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
    */
