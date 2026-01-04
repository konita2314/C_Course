#include <stdio.h>
void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
int main()
{
    int a,b;
    printf("Input a & b:\n");
    scanf("%d %d",&a,&b);
    printf("before: a = %d, b = %d\n",a,b);
    swap(&a,&b);
    printf("after: a = %d, b = %d",a,b);
    return 0;
}
