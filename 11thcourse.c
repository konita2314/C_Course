#include <stdio.h>

int main(void)
{
    float grade, rate;
    printf("请输入成绩: ");
    scanf("%f", &grade);
    printf("请输入出勤率(0-1之间): ");
    scanf("%f", &rate);
    if (grade >= 85 && rate >= 0.9)
        printf("获得一等奖学金\n");
    else if (grade >= 85 && rate <= 0.9)
        printf("获得二等奖学金\n");
    else if (grade >= 85 && rate >= 0.95)
        printf("获得三等奖学金\n");
    else
        printf("未获得奖学金\n");
    return 0;
}