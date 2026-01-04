#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//真正的随机数//
int main(void)
{
    int i;
    srand((unsigned int)time(NULL));//用当前时间作为随机数种子
    //unsigned int是无符号整数类型，time(NULL)返回当前时间的秒数
    //这样每次运行程序时，种子都会不同
    i = rand()%101;
    printf("生成的随机数是: %d\n", i);
    //这就是真正的随机数
    return 0;
}