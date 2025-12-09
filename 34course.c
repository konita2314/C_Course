#include <stdio.h>
#include <string.h>
#define N 19
int main()
{
    char lang[N];
    snprintf(lang, N, "C17 standard");//snprintf to avoid buffer overflow
    printf("Programming Language: %s\n", lang);

    char text[N];
    scanf("%18s", text); // limit input to avoid buffer overflow
    printf("You entered: %s\nThe length is %lu\n", text, strlen(text));// Warning: <string.h> strlen returns size_t
    return 0;
}
