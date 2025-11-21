#include <stdio.h>
#define datasize 40

int main()
{
    int min = datasize, max = 0;
    int members = 0;
    int table[datasize];
    for (int i = 0; i < datasize; i++)
    {
        printf("input numbers\n");
        scanf("%d", &table[i]);
        if (table[i] > max)
        {
            max = table[i];
        }
        if (table[i] < min)
        {
            min = table[i];
        }
        if (table[i] >= 60)
        {
            members++;
        }
    }
    printf("The result:\nmembers:%d\nnonmenbers:%d\nmin:%d\nmax;%d\n", members, datasize - members, min, max);
}