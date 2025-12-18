#include  <stdio.h>
#define N 80
char *fun (char tt[ ]);
int main(void)
{
    char str[N];
    printf("请输入一个字符串：\n");
    gets(str);
    printf("转换的结果是: %s\n", fun(str));
    return 0;
}
char *fun (char tt[ ])
{
    
}