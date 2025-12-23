#include <stdio.h>
#define N 40
int IfIsRight(char TEXT[])
{
    int i = 0;
    while (TEXT[i] != '\0')
    {
        i++;
    }
    for (int j = 0; j < (i / 2); j++)
    {
        if (TEXT[j] != TEXT[i - 1 - j])
        {
            return 1;
        }
    }
    return 0;
}   
int main()
{
    char text[N];
    scanf("%s", text);
    if (IfIsRight(text) == 0)
    {
        printf("is!");
    }
    else
    {
        printf("is not!");
    }
    return 0;
}
