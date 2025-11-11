#include <stdio.h>
#include <stdlib.h>
int istruenumber(int num)
{
    int a, b;
    if (num < 2)
    {
        printf("Please input a (>=2)natural number!");
        return -1;
        exit(0);
    }
    for (a = 2;a <= num - 1; a++)
    {
        if (num % a == 0)
        {
            printf("NO");
            return 1;
            break;
        }
        else
        {
            printf("YES");
            return 0;
            break;
        }
    }
}
int main()
{
    int i;
    scanf("%d",&i);
    istruenumber(i);
}