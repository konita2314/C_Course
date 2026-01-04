#include <stdio.h>
int main()
{
    int a, b, c;
    int d = 0;
    for (a = 1; a <= 4; a++)
    {
        for (b = 1; b <= 4; b++)
        {
            for (c = 1; c <= 4; c++)
            {
                if (a != b && b != c && a != c)
                {
                    printf("%2d%d%d", a, b, c);
                    d++;
                }
            }
        }
        printf("\n");
    }
    printf("共有%d种情况", d);
    return 0;
}