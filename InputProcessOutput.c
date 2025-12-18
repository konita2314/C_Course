#include <stdio.h>
//计算三位数的各个位数。只能用于三位数。
int main(void){
    int x,b2,b1,b0;//声明变量
    scanf("%d", &x);
    b2 = x / 100;//百位。需要注意，在C中，这个斜杠表示整数除法，输出的结果是整数部分。
    b1 = (x / 10) % 10;//十位。%10表示
    b0 = x % 10;//个位
    printf("Digits: %d %d %d\n", b2, b1, b0);
    return 0;
}