#include <stdio.h>
int main(void)
{
    int data1, data2;
    char op;
    printf("请输入两个整数和一个运算符(例如: 3 + 4): ");
    scanf("%d %c %d", &data1, &op, &data2);
    switch (op)
    {
        case '+':
        printf("%d %c %d = %d\n", data1, op, data2, data1 + data2);
        break;
    case '-':
        printf("%d %c %d = %d\n", data1, op, data2, data1 - data2);
        break;
    case '*':
        printf("%d %c %d = %d\n", data1, op, data2, data1 * data2);
        break;
    case '/':
        if (data2 != 0)
            printf("%d %c %d = %.2f\n", data1, op, data2, (float)data1 / data2);//注意强制类型转换
        else
            printf("错误: 除数不能为零!\n");
            break;
    default:
        printf("错误: 不支持的运算符 %c\n", op);
        break;
    }
    return 0;
}