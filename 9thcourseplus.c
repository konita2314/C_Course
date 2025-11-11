#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 0.00001 //定义一个很小的数,用来判断浮点数是否等于0

int main()
{
    float a, b, c, disc, root1, root2, realPart, imagPart;
    printf("请输入三个数: ");
    scanf("%f %f %f", &a, &b, &c);
    if (fabs(a) <= EPS) //判断是否为线性方程
    {
        if (fabs(b) <= EPS)
        {
            if (fabs(c) <= EPS)
                printf("方程有无穷多解\n");
            else
                printf("方程无解\n");
        }
        else
        {
            root1 = -c / b;
            printf("方程有唯一解: x=%.2f\n", root1);
        }
    }
    else
    {
        disc = b * b - 4 * a * c; //计算判别式
        if (disc > EPS)
        {
            root1 = (-b + sqrt(disc)) / (2 * a);
            root2 = (-b - sqrt(disc)) / (2 * a);
            printf("方程有两个不等实根: x1=%.2f, x2=%.2f\n", root1, root2);
        }
        else if (fabs(disc) <= EPS)
        {
            root1 = -b / (2 * a);
            printf("方程有一个实根: x=%.2f\n", root1);
        }
        else
        {
            realPart = -b / (2 * a);
            imagPart = sqrt(-disc) / (2 * a);
            printf("方程有两个共轭复根: x1=%.2f+%.2fi, x2=%.2f-%.2fi\n", realPart, imagPart, realPart, imagPart);
        }
    }
}