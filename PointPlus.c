#include <stdio.h>

void plus(int *a, int *b, int *c);

int main()
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    plus(&x, &y, &z);
    printf("%d %d %d", x, y, z);
    return 0;  // 建议加上return语句
}

// 给三个整数加1
void plus(int *a, int *b, int *c)
{
    (*a)++;  // *a 表示"取a指向的值"，然后加1
    (*b)++;
    (*c)++;
}
