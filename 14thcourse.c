#include <stdio.h>
#include <math.h>
int main()
{
    float a, b, c;
    printf("请输入三角形的三条边长: ");
    scanf("%f %f %f", &a, &b, &c);
    if(a + b > c && a + c > b && b + c > a)
    {
        float s = (a + b + c) / 2;//计算半周长
        float area = sqrt(s * (s - a) * (s - b) * (s - c));//使用海伦公式计算面积
        printf("是三角形，其面积为: %.2f\n", area);
    }
    else
    {
        printf("输入的边长不能构成三角形!\n");
    }
}