#include <stdio.h>

int main(void) 
{
    int a;
    char b;
    float c;
    
    printf("请输入三个值（例如: 100 A 3.14）: ");
    scanf("%d %c %f", &a, &b, &c);//这样就完美规避了空格和换行符的问题
    printf("整数是:%d\n字符是:%c\n浮点数是:%.2f\n", a, b, c);
    return 0;
}