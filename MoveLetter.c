#include <stdio.h>
#define N 80
int main(void)
{
    char str[N];
    int i = 0;
    printf("请输入一个字符串：\n");
    gets(str);//注意：gets不安全，可能导致数据溢出，推荐使用fgets！
    while (str[i] != '\0')
    {
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
            str[i] = str[i] + 3;
        i++;
    }
    printf("转换的结果是: %s\n", str);
    return 0;
}