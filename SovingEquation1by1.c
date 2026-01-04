#include <stdio.h>
// 鸡5 母鸡3 小鸡1/3 100元买100鸡
int main()
{
    int i, j, k;
    int l = 0;
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {
            for (k = 0; k < 100; k++)
            {
                if (5 * i + 3 * j + (k) / 3 == 100 && i + j + k == 100 && k % 3 == 0)
                {
                    printf("---\ncock%2d\nhen%2d\nchicken\n", i, j, k);
                    l++;
                }
            }
        }
    }
    printf("---\ntotal %d solutions", l);
    return 0;
}