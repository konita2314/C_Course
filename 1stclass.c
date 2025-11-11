#include <stdio.h>
//欢迎来到C语言的世界//
//输入三个整数并输出
int main(void){
    int a , b ,c;
    scanf("%d %d %d", &a, &b ,&c);//输入三个整数，其中输入时以空格、加号、逗号分隔，回车结束。&表示取变量的地址
    printf("Values:%d %d %d\n", a, b, c);//%d表示输出整数，“a,b,c”表示输出变量
    return 0;
}