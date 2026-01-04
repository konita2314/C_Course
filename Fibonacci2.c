#include <stdio.h>
#include <time.h>   // 用于clock()
#include <sys/time.h> // 用于gettimeofday() - 更高精度

// 原迭代版本
int fibb(int num)
{
    int a = 1, b = 1, c;
    // 注意：这里scanf的位置有问题，应该在main中调用前输入
    // scanf("%d", &num); // 这行应该移除或调整
    
    if (num < 1)
    {
        return -1;
    }
    if (num == 1 || num == 2)
    {
        return 1;
    }
    else
    {
        for (int j = 3; j <= num; j++)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
}

// 递归版本用于计时
int fib_recursive(int n)
{
    if (n <= 0) return -1;
    if (n == 1 || n == 2) return 1;
    return fib_recursive(n-1) + fib_recursive(n-2);
}

int main()
{
    int i, result;
    struct timeval start, end;
    long seconds, microseconds;
    double elapsed;
    
    // 获取用户输入
    printf("Enter Fibonacci number position: ");
    scanf("%d", &i);
    
    // ========== 方法1：使用gettimeofday() - 微秒精度 ==========
    printf("\n=== Timing with gettimeofday() (microsecond precision) ===\n");
    
    gettimeofday(&start, NULL);  // 开始计时
    result = fib_recursive(i);   // 调用递归版本
    gettimeofday(&end, NULL);    // 结束计时
    
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    
    printf("Fibonacci(%d) = %d\n", i, result);
    printf("Recursive time: %.6f seconds\n", elapsed);
    
    // ========== 方法2：使用clock() - CPU时间 ==========
    printf("\n=== Timing with clock() (CPU time) ===\n");
    
    clock_t start_cpu = clock();   // 开始计时
    result = fib_recursive(i);     // 再次调用（注意这会重复计算）
    clock_t end_cpu = clock();     // 结束计时
    
    double cpu_time_used = ((double)(end_cpu - start_cpu)) / CLOCKS_PER_SEC;
    
    printf("Fibonacci(%d) = %d\n", i, result);
    printf("CPU time: %.6f seconds\n", cpu_time_used);
    
    // ========== 使用迭代版本对比 ==========
    printf("\n=== Iterative version for comparison ===\n");
    
    gettimeofday(&start, NULL);    // 开始计时
    result = fibb(i);              // 调用迭代版本
    gettimeofday(&end, NULL);      // 结束计时
    
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    
    printf("Fibonacci(%d) = %d\n", i, result);
    printf("Iterative time: %.6f seconds\n", elapsed);
    
    return 0;
}