#include <stdio.h>
int main()
{
    //玩点刺激的：九九乘法表
    for (int m = 1; m <= 9; m = m + 1)
    {
        for (int n = 1; n <= m; n = n + 1)
        {
            printf("%d*%d=%-2d ", n, m, n * m);//%-2d表示左对齐，占2个字符宽度，这是为了让输出更整齐
        }
        printf("\n");
    }
}