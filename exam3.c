#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 列举库
/*
想一下，怎么实现这个程序。
首先，我们有一份完整的名单，可以把它存储成字符串列表的形式。
我们要进行随机分组，应该怎么做？假设两个人一个组。
*第一个问题：表单里有多少人？
    直接for解决。
        for (int i = 0;i < n,i++)
        {
            namelist[i]；
        }
    最后i = n，直接输出。
    也可以：
    number = sizeof(namelist) / sizeof(name[0])
    注意：如果名单上人员字符长度不定，那么这个方法不大管用。
    第三种办法：
    int count = 0;
        while (namelist[count] != NULL) // 假设以 NULL 结尾
        {

            count++;
        }
*第二个问题：遍历名单。把上面的结构变成printf("%s",namelisy[i])。
*第三个问题：如何准确找到人
    namelist[i] 即可（注意表单以0开始）
*第四个问题：
*/
void main()
{
}