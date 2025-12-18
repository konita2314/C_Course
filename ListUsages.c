#include <stdio.h>
#define NUM 10
int main()
{
    int score[NUM];
    for (int i = 1; i <= NUM; i++)
    {
        score[i] = i;
        printf("%d\n",score[i]);
    }
    return 0;
}