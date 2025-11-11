#include <stdio.h>
#include <time.h>
int main()
{
    time_t current_time;
    time(&current_time);
    printf("Current time in seconds since epoch: %lld\n", (long long)current_time);
    
    return 0;
}