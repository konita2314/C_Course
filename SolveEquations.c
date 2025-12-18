#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 0.00001//定义一个很小的数,用来判断浮点数是否等于0
//因为浮点数在计算机中存储时会有误差,不能直接用==来判断是否等于0，而是要判断其绝对值是否小于一个很小的数EPS
//EPS表示误差范围，如果一个浮点数的绝对值小于EPS，就可以认为它等于0，不能取0是因为计算机存储浮点数时会有精度损失，而EPS就是用来弥补这种精度损失的
int main(void)
{
    double a,b,c,d,e;
    printf("请输入三个数: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    if (fabs(a)<=EPS)//这是在判断a是否等于0。fabs是取绝对值函数
    {
        if (fabs(b)<=EPS)
        {
            if (fabs(c)<=EPS)
                printf("方程有无穷多解\n");
            else
                printf("方程无解\n");
        }
        else
        {
            d = -c/b;
            printf("方程有唯一解: x=%.2f\n", d);
        }
    }
    else
    {
        d = b*b - 4*a*c;
        if (d > EPS)
        {
            e = (-b + sqrt(d)) / (2*a);//sqrt是开平方函数
            d = (-b - sqrt(d)) / (2*a);
            printf("方程有两个不等实根: x1=%.2f, x2=%.2f\n", e, d);
        }
        else if (fabs(d)<=EPS)//小于等于是因为浮点数可能有误差，不能直接用==来判断
        {
            d = -b / (2*a);
            printf("方程有一个实根: x=%.2f\n", d);
        }
        else
            printf("方程无实根\n");
    }
}