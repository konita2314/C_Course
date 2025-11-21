#include <stdio.h>

long fib(int n)
{
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    
    int a = 1, b = 1;
    for (int i = 3; i <= n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%ld", fib(n));
    return 0;
}
//我有一个伟大的想法，可惜一行代码太小写不下