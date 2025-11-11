#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 0.00001//定义一个很小的数
int main(void)
{
    printf("%f\n",EPS);//普通浮点数输出
    printf("%e\n",EPS);//科学计数法输出
    return 0;
}