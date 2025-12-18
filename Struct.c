#include <stdio.h>
typedef struct date
{
    int year;
    int month;
    int day;
}DATE;
typedef struct student
{
    int number;
    char name[20];
    char gender;
    DATE birthday;
}STUDENT;
