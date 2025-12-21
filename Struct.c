#include <stdio.h>
#include <string.h>  // 需要添加这个头文件来处理字符串

#define N 15  // 假设学号最长为15位（可以调整）

typedef struct date
{
    int year;
    int month;
    int day;
} DATE;

typedef struct student
{
    char studentID[N];    /* 学号改为字符数组 */
    char studentName[20]; /* 姓名 */
    char stuGender;       /* 性别 */
    DATE birthday;        /* 出生日期 */
    int score[4];         /* 4门课程的成绩 */
} STUDENT;

int main(void)
{
    STUDENT stu1, stu2;
    int i;
    
    printf("Input a record:\n");
    
    // 输入学号（字符串，不需要&）
    printf("学号: ");
    scanf("%s", stu1.studentID);
    
    printf("姓名: ");
    scanf("%s", stu1.studentName);
    
    printf("性别(M/F): ");
    scanf(" %c", &stu1.stuGender);  // %c前有空格，跳过空白字符
    
    printf("生日(年 月 日): ");
    scanf("%d %d %d", 
          &stu1.birthday.year, 
          &stu1.birthday.month, 
          &stu1.birthday.day);
    
    printf("四门课程的成绩: ");
    for (i = 0; i < 4; i++)
    {
        scanf("%d", &stu1.score[i]);
    }
    
    stu2 = stu1;
    
    printf("\n&stu2 = %p\n", &stu2);
    
    // 打印学生信息
    printf("\n=== 学生信息 ===\n");
    printf("学号: %s\n", stu2.studentID);
    printf("姓名: %s\n", stu2.studentName);
    printf("性别: %c\n", stu2.stuGender);
    printf("生日: %d年%02d月%02d日\n", 
           stu2.birthday.year, 
           stu2.birthday.month, 
           stu2.birthday.day);
    printf("成绩: %d, %d, %d, %d\n", 
           stu2.score[0], 
           stu2.score[1], 
           stu2.score[2], 
           stu2.score[3]);
    
    return 0;
}