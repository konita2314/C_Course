#include  <stdio.h>
#define N 80
char *MyStrcat(char *dstStr, char *srcStr);
int main(void)
{
    char first[2*N];   /* 这个数组应该足够大，以便存放连接后的字符串 */
    char second[N];
    printf("Input the first string:");
    gets(first);
    printf("Input the second string:");
    gets(second);
    printf("The result is: %s\n", MyStrcat(first, second));
    return 0;
}
/* 函数功能：将字符串srcStr连接到字符串dstStr的后面 */
char *MyStrcat(char *dstStr, char *srcStr)
{
    char *pStr = dstStr;   /* 保存字符串dstStr的首地址 */
    /* 将指针移到字符串dstStr的末尾 */
    while (*dstStr != '\0')
    {
        dstStr++;
    }
    /* 将字符串srcStr复制到字符串dstStr的后面 */
    for(; *srcStr!='\0'; dstStr++, srcStr++)
    {
        *dstStr = *srcStr;
    }
    *dstStr = '\0';      /* 在连接后的字符串的末尾添加字符串结束标志 */
    return pStr;         /* 返回连接后的字符串dstStr的首地址 */
}