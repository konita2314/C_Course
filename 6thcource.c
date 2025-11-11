#include <stdio.h>

int main(void) 
{
    char ch;
    ch = getchar(); // 从标准输入读取一个字符。
    //注意是一个字符，不是一个字符串。如果函数括号内有内容，则表示从指定的文件流中读取字符。如果括号内为空，则表示从标准输入读取字符。
    putchar(ch);   // 将读取的字符输出到标准输出,这是一个回显，意思是输入什么就输出什么

    // 清空输入缓冲区,避免影响后续的输入操作
    while (getchar() != '\n');

    char ch1;
    scanf("%c", &ch1); // 从标准输入读取一个字符。注意空格，表示跳过所有空白字符（包括空格、制表符和换行符），直到遇到一个非空白字符为止。
    printf("%c\n", ch1); // 将读取的字符输出到标准输出
    //跟以上相比，scanf和printf更通用，可以处理多种数据类型，而getchar和putchar专门用于字符处理。
    return 0;
}
/*注意：
#include <stdio.h>

int main(void) 
{
    char ch;
    ch = getchar();    // 你输入: A + 回车
    putchar(ch);       // 输出: A
    
    char ch1;
    scanf("%c", &ch1); // 自动读取了缓冲区中的 \n
    printf("[%c]\n", ch1); // 输出: [] 或 [换行]
    
    return 0;
}
*/