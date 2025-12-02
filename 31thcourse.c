#include <stdio.h>
#define N 4
void main()
{
    long int name[N];
    int lib[N];

    for (int i = 0; i < N; i++)
    {
        printf("Input number:\n");
        scanf("%d", &name[i]);
        printf("Input grades:\n");
        scanf("%d", &lib[i]);
    }

    printf("==LIST==\n");
    printf("%7s|%3s\n", "Number", "Grade");
    for (int i = 0; i < N; i++)
    {
        printf("%7ld|%3d\n", name[i], lib[i]);
    }

    float avr;
    int all = 0;
    for (int i = 0; i < N; i++) // 修正循环条件
    {
        all += lib[i];
    }
    avr = (float)all / N;
    printf("The averange is %-2d \n", avr);

    int max = 0;
    int min = N;
    for (int i = 0; i < N; i++)
    {
        if (lib[i] > max)
        {
            max = lib[i];
        }
        if (lib[i] < min)
        {
            min = lib[i];
        }
    }
    printf("%7s|%3s\n%7d|%3d\n", "MAX", "MIN", max, min);
}