#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    
    int target = rand() % 101;  // 随机目标值 0-100
    int low = 0;
    int high = 100;
    int guess;
    int counter = 0;
    
    printf("寻找随机数字 (范围: 0-100)\n");
    
    while (low <= high)
    {
        counter++;
        guess = (low + high) / 2;
        
        printf("第%d次猜测: %d (目标: %d)\n", counter, guess, target);
        
        if (guess == target)
        {
            printf("成功！\n");
            printf("总次数: %d\n", counter);
            break;
        }
        else if (guess < target)
        {
            low = guess + 1;
        }
        else
        {
            high = guess - 1;
        }
    }
    
    return 0;
}