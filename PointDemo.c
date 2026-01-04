#include <stdio.h>
int main()
{
    int a = 0, b = 1;
    char c = 'A';
    printf("a(%d) is %p,\nb(%d) is %p,\nc(%c) is %p\n", a, a, b, b, c, c);
    int *pa, *pb;
    char *pc;
    pa = &a;
    pb = &b;
    pc = &c;
    printf("%d\n%d\n%c\n",pa,pb,pc);
}