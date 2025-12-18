#include <stdio.h>
int fibb(int num)
{
    int a = 1, b = 1, c;
    scanf("%d", &num);
    if (num < 1)
    {
        return -1;
    }
    if (num == 1 || num == 2)
    {
        return 1;
    }
    else
    {
        for (int j = 3; j <= num; j++)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
}
int main() // example
{
    /*Your code goes here.*/
    // 1 2 3 4 5 6  7  8  9
    // 1 1 2 3 5 8 13 21 34
    int i;
    printf("%d", fibb(i));
    return 0;
}