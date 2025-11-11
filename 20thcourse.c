#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i;
    int m;
    i = rand()%101;//生成一个随机数，区间[0, 100]。%101表示取余数
    //取余数是因为
    //生成一个随机数，区间[0, RAND_MAX]
    printf("please input a number:\n");
    while (i > 0 || i < 100)
    {
        scanf("%d", &m);
        if (i < m)
        {
            printf("Too big!\n");
        }
        else if (i == m)
        {
            printf("You're right!\n");
            break;
        }
        else
        {
            printf("Too small!\n");
        }
    }
    return 0;
}