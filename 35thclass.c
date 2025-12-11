#include <stdio.h>
#define N 150
#define LENGTH 100  // 增加长度，10太短了

int main()
{
    char name[N][LENGTH];
    int i;
    
    printf("How many people? (max %d): ", N);
    if (scanf("%d", &i) != 1) {
        printf("Invalid input!\n");
        return 1;
    }
    
    // 添加边界检查
    if (i <= 0 || i > N) {
        printf("Number must be between 1 and %d\n", N);
        return 1;
    }
    
    // 清空输入缓冲区，防止后续输入问题
    while (getchar() != '\n');
    
    for (int a = 0; a < i; a++)
    {
        printf("Input name %d/%d: ", a + 1, i);
        // 修正：使用 %s 而不是 %d
        // 使用 fgets 可以读取包含空格的名字
        fgets(name[a], LENGTH, stdin);
        
        // 移除末尾的换行符
        int len = 0;
        while (name[a][len] != '\0') {
            if (name[a][len] == '\n') {
                name[a][len] = '\0';
                break;
            }
            len++;
        }
    }
    
    printf("\nAll names:\n");
    for (int b = 0; b < i; b++)
    {
        // 数组名本身就是地址，不需要 &
        printf("%d. %s\n", b + 1, name[b]);
    }
    
    return 0;
}