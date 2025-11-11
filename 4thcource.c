#include <stdio.h>
int main(void)
{
    printf("char:%zu\n", sizeof(char)); //%zu是专门用来输出size_t类型的格式说明符
    printf("int:%zu\n", sizeof(int));
    printf("float:%zu\n", sizeof(float));

    // printf("headfile:%d\n",sizeof(stdio.h))//输出头文件大小 (无效用法，已注释)

    return 0;
}