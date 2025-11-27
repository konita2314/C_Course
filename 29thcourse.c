#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 100

int main()
{
    srand(time(NULL));
    int score[NUM];

    printf("formal data:\n");
    for (int i = 0; i < NUM; i++) // Fixed: start from 0, go to NUM-1
    {
        score[i] = rand() % 100 + 1;
        printf("%-3d ", score[i]);
        if ((i + 1) % 10 == 0)
            printf("\n"); // Optional: better formatting
    }

    printf("\nNOW RANGING...\n");

    // Correct bubble sort implementation
    for (int j = 0; j < NUM - 1; j++)
    {
        for (int k = 0; k < NUM - j - 1; k++)
        {
            if (score[k] < score[k + 1]) // For descending order
            {
                int temp = score[k];
                score[k] = score[k + 1];
                score[k + 1] = temp;
            }
        }
    }

    printf("the result:\n");
    for (int l = 0; l < NUM; l++) // Fixed: start from 0, go to NUM-1
    {
        printf("%-3d ", score[l]);
        if ((l + 1) % 10 == 0)
            printf("\n"); // Optional: better formatting
    }

    return 0;
}