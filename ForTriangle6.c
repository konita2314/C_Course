#include <stdio.h>
int main()
{
    int i, j, k, l;
    scanf("%d",&i);
    printf("正方形\n");
    for (j = 0;i > j;j++)
    {
        for(k = 0;i > k;k++)
        {
            printf("*");
        }
        printf("\n");
    }
    printf("左下角三角形\n");
    for (j = 0;i > j;j++)
    {
        for (k = 0; k <= j ; k++)
        {
            printf("345 徐佳鑫 ");
        }
        printf("\n");
    }
    printf("右下角三角形\n");
    for (j = 0;i > j;j++)
    {
        for (l = 0;l <= i - j - 2;l++)
        {
            printf("          ");
        }
        for (k = 0; k <= j ; k++)
        {
            printf("345 徐佳鑫");
        }
        printf("\n");
    }
    
    return 0;
}