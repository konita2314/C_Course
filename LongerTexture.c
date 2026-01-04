//比较两个字符串，将长的那个字符串的首地址作为函数返回。
#include  <stdio.h>
#define N 80
char *fun(char *s,char *t);
int main(void)
{
    char first[2*N];   /* 这个数组应该足够大，以便存放连接后的字符串 */
    char second[N];
    printf("Input the first string:");
    gets(first);
    printf("Input the second string:");
    gets(second);
    printf("The longer is: %s\n", fun(first, second));
    return 0;
}
char *fun(char *s, char *t)
{
    int len_s = 0, len_t = 0;
    
    // 手动计算 s 的长度
    while (s[len_s] != '\0') {
        len_s++;
    }
    
    // 手动计算 t 的长度
    while (t[len_t] != '\0') {
        len_t++;
    }
    
    // 返回较长的字符串的地址
    if (len_s >= len_t) {
        return s;
    } else {
        return t;
    }
}