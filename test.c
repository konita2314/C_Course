#include <stdio.h>
#include <stdbool.h>

// 函数声明
bool isLeapYear(int year);
int getDaysInMonth(int year, int month);
int calculateDayOfWeek(int year, int month, int day);
void printDayOfWeek(int dayOfWeek);

// 主函数
int main() {
    int year, month, day;
    
    printf("日期转星期计算器\n");
    printf("================\n");
    
    // 输入日期
    printf("请输入年份: ");
    scanf("%d", &year);
    
    printf("请输入月份 (1-12): ");
    scanf("%d", &month);
    
    printf("请输入日期: ");
    scanf("%d", &day);
    
    // 验证日期合法性
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > getDaysInMonth(year, month)) {
        printf("错误: 输入的日期不合法！\n");
        return 1;
    }
    
    // 计算星期几
    int dayOfWeek = calculateDayOfWeek(year, month, day);
    
    // 输出结果
    printf("\n计算结果:\n");
    printf("%d年%d月%d日是 ", year, month, day);
    printDayOfWeek(dayOfWeek);
    printf("\n");
    
    return 0;
}

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取某年某月的天数
int getDaysInMonth(int year, int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

// 计算星期几的函数 (使用Zeller公式)
int calculateDayOfWeek(int year, int month, int day) {
    // 如果是1月或2月，当作前一年的13月或14月处理
    if (month < 3) {
        month += 12;
        year--;
    }
    
    int century = year / 100;
    int yearOfCentury = year % 100;
    
    // Zeller一致性公式
    int h = (day + 13*(month+1)/5 + yearOfCentury + yearOfCentury/4 + century/4 - 2*century) % 7;
    
    // 调整结果，使0=星期六, 1=星期日, ..., 6=星期五
    if (h < 0) {
        h += 7;
    }
    
    return h;
}

// 打印星期几
void printDayOfWeek(int dayOfWeek) {
    switch (dayOfWeek) {
        case 0:
            printf("星期六");
            break;
        case 1:
            printf("星期日");
            break;
        case 2:
            printf("星期一");
            break;
        case 3:
            printf("星期二");
            break;
        case 4:
            printf("星期三");
            break;
        case 5:
            printf("星期四");
            break;
        case 6:
            printf("星期五");
            break;
        default:
            printf("未知");
    }
}