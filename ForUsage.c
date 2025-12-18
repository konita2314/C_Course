#include <stdio.h>
#include <math.h>

int main()
{
    int i,j,k;
    int c = 0;
    for (i=1;i<10;i++)
    {
        for (j=0;j<10;j++)
        {
            for (k=0;k<10;k++)
            {
                if(pow(i,3)+pow(j,3)+pow(k,3)==i*100+j*10+k)
                {
                    printf("The number includes %d\n",i*100+j*10+k);
                    c++;
                }
            }
        }
    }
    printf("%d times processed.",c);
    return 0;
}