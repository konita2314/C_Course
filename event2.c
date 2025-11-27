#include <stdio.h>
#define size 12
int main()
{
    int year;
    int month;
    int months[size];
    for (int i; i <= 12; i++)
    {
        if (i == 2)
        {
            if (year % 4 == 0 && year / 400 == 0)
            {
                months[i] = 28;
            }
            else
            {
                months[i] = 29;
            }
        }
        if (i == 1 && 3 && 5 && 7 && 8 && 10 && 12)
        {
            months[i] = 31;
        }
        else
        {
            months[i] = 30;
        }
    }
    scanf("%d %d",&year,&month);
    printf("%d days a month",months[month]);
    return 0;
}