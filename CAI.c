#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand((unsigned int)time(NULL)); // 用当前时间作为随机数种子
    
    int a = rand() % 11;
    int t = rand() % 4; // 生成整数范围：0,1,2,3
    char op;
    int b = rand() % 11;
    
    // 修正：除法时确保分母不为0
    while (b == 0 && t == 3)
        b = rand() % 11;
    
    // 修正：C语言用if-else if，不是elif
    if (t == 0)
    {
        op = '+';
    }
    else if (t == 1)
    {
        op = '-';
    }
    else if (t == 2)
    {
        op = '*';
    }
    else
    {
        op = '/';
    }
    
    int ans;
    // 修正：switch语句格式和变量声明
    switch (op)
    {
        case '+':
            printf("%d%c%d=\n", a, op, b); // 修正：去掉&，变量前加逗号
            ans = a + b;
            break; // 重要：需要break
        case '-':
            printf("%d%c%d=\n", a, op, b);
            ans = a - b;
            break;
        case '*':
            printf("%d%c%d=\n", a, op, b);
            ans = a * b;
            break;
        case '/':
            printf("%d%c%d=(Keep the integer)\n", a, op, b);
            ans = a / b; // 修正：整数除法
            break;
    }
    
    int ins;
    scanf("%d", &ins); // 修正：scanf需要&
    
    if (ins == ans)
    {
        printf("Correct!\n");
    }
    else
    {
        printf("Incorrect!\n"); // 修正：printf拼写
    }
    
    return 0;
}