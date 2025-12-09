#include <stdio.h>

void swit(int *a, int *b);

int main()
{
    int x, y;  // 先创建两个实际的整数变量
    int *a = &x, *b = &y;  // 让指针指向这些变量
    
    scanf("%d %d", &x, &y);  // 或者 a, b（因为 a=&x, b=&y）
    swit(&x, &y);  // 传递地址
    printf("%d %d", x, y);
    return 0;
}
// 哈基米哦南北路多
void swit(int *a, int *b)
{
    int temp;
    temp = *a;  // *a 表示"取 a 指向的值"
    *a = *b;    // 将 b 指向的值赋给 a 指向的位置
    *b = temp;  // 将 temp 赋给 b 指向的位置
}