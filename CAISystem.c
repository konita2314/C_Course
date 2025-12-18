#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomnum()
{
    return rand() % 10 + 1;
}

char randomop()
{
    int i;
    char j;
    i = rand() % 4 + 1;
    switch (i)
    {
    case 1:j = '+';
        break;
    case 2:j = '-';
        break;
    case 3:j = '*';
        break;
    case 4:j = '/';
        break;
    }
    return j;
}

int check(int a, char op, int b, int res)
{
    int m;
    switch (op)
    {
    case '+':m = a + b;
        break;
    case '-':m = a - b;
        break;
    case '*':m = a * b;
        break;
    case '/':m = a / b;
        break;
    }
    if (m == res)
    {
        printf("Correct!\n");
        return 1; // 返回1表示正确
    }
    else
    {
        printf("Incorrect!\n");
        return 0; // 返回0表示错误
    }
}

int main()
{
    system("cls");
    printf("========CAI For Caculates========\n*YOU HAVE TEN CHANCES TO TRY TO SOLVE THE PROBLEMS*\n");
    int a, b, c, ans, righttotal = 0;
    char op;
    srand(time(NULL));

    for (c = 0; c < 10; c++)
    {
        do // 循环来控制整数除法
        {
            a = randomnum();
            b = randomnum();
            op = randomop();
            // 如果是除法，确保能整除且除数不为0
            if (op == '/' && (b == 0 || a % b != 0))
            {
                continue; // 重新生成
            }
            else
            {
                break; // 符合条件，退出循环
            }
        } while (1);
        
        printf("%d %c %d = ?\n", a, op, b);
        
        // 修正输入验证逻辑
        int correct = 0;
        do
        {
            scanf("%d", &ans);
            if (check(a, op, b, ans)) // 直接调用check函数检查答案
            {
                righttotal++;
                correct = 1;
            }
            else
            {
                printf("Try again!\n");
            }
        } while (!correct); // 直到答对才继续下一题
    }
    
    printf("You have tried 10 times and %d time(s) are correct.\n", righttotal);
    return 0;
}