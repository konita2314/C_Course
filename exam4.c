#include <stdio.h>
#define N 20
int main()
{
    char text[N] = "characteristic"; // 如果改成输入，可以使用gets(text)。有区别吗？
    int ch;
    int i, j;
    printf("%s\n", text);
    printf("Delete which chart?\n");
    ch = getchar();
    for (i = j = 0; text[i] != '\0'; i++)
    {
        if (text[i] != ch)
        {
            text[j++] = text[i];
        }
    }
    text[j] = '\0';
    printf("%s\n", text);

    return 0;
}