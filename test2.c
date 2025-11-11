#include <stdio.h>
int main(void)
{
    int a, b;
    printf("");
    for (a = 1; a <=9; a++)
    //for的三个参数：初始化条件；循环条件；迭代条件
    //分别表示：循环变量的初始值；循环继续的条件；每次循环结束后变量的变化。
    //每一个参数都可以省略，但两个分号不能省略
    {
        for (b = 1; b <= a; b++)
        {
            printf("%d*%d=%-2d ", b, a, a*b);//%-2d表示占2个字符宽度，从而实现左对齐
        }
        printf("\n");
    }
}
//如果使用while：
    /*
    a = 1;
    while (a <= 9)
    {
        b = 1;//外层循环每次执行时，都要初始化内层循环变量
        while (b <= a)
        {
            printf("%d*%d=%-2d ", b, a, a*b);
            b = b + 1;
        }
        printf("\n");
        a = a + 1;
    }
    */