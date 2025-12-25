#include <stdio.h>
// 将一个十进制整数转换为二进制整数，可以采用“除2取余，逆序排列”的方法。具体操作如下：
// 首先，用2去除该十进制整数，记录所得的余数，并将商作为新的被除数；然后，继续用2去除新的被除数，记录新的余数，并将所得的商作为下一轮计算的被除数。
// 如此重复此过程，直到商为零为止。此时，将所有记录的余数按照获取顺序的逆序排列，即最早得到的余数作为二进制数的最低位，最后得到的余数作为最高位，依次排列.
// 即可得到该十进制整数对应的二进制表示。
#include <stdio.h>
int main()
{
    int decimal, remainder, binary[32], i = 0;
    printf("请输入一个十进制数:\n");
    scanf("%d", &decimal);
    if (decimal == 0)
    {
        printf("该数的二进制数为: 0\n");
        return 0;
    }
    while (decimal > 0)
    {
        remainder = decimal % 2;
        binary[i] = remainder;
        decimal = decimal / 2;
        i++;
    }
    printf("该数的二进制数为: ");
    for (i--; i >= 0; i--)
    {
        printf("%d", binary[i]);
    }
    printf("\n");
    return 0;
}
// 进阶任务：把算法用函数封装、这个数用长整数表示如何？