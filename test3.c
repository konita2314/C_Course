#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// 内存遍历函数
void memory_walker(const void *start_addr, size_t size, int bytes_per_line) {
    const unsigned char *ptr = (const unsigned char *)start_addr;
    const unsigned char *end_ptr = ptr + size;
    
    printf("\n=== 内存遍历: 从地址 %p 开始, 大小 %zu 字节 ===\n\n", start_addr, size);
    
    int line_count = 0;
    while (ptr < end_ptr) {
        // 打印地址
        printf("%08lx: ", (unsigned long)(ptr - (unsigned char *)start_addr));
        
        // 打印16进制值
        for (int i = 0; i < bytes_per_line; i++) {
            if (ptr + i < end_ptr) {
                printf("%02x ", *(ptr + i));
            } else {
                printf("   "); // 不足的部分用空格填充
            }
            
            // 每4个字节加一个空格，便于阅读
            if ((i + 1) % 4 == 0 && i != bytes_per_line - 1) {
                printf(" ");
            }
        }
        
        printf(" | ");
        
        // 打印ASCII字符
        for (int i = 0; i < bytes_per_line; i++) {
            if (ptr + i < end_ptr) {
                unsigned char c = *(ptr + i);
                // 只打印可打印字符，其他用点表示
                printf("%c", (c >= 32 && c <= 126) ? c : '.');
            }
        }
        
        printf(" |\n");
        
        ptr += bytes_per_line;
        line_count++;
        
        // 每16行暂停一下
        if (line_count % 16 == 0) {
            printf("\n按回车继续...");
            getchar();
        }
    }
    
    printf("\n=== 内存遍历完成 ===\n");
}

// 安全的遍历示例
void safe_memory_demo() {
    printf("=== 内存遍历演示 ===\n\n");
    
    // 示例1: 遍历一个字符串
    char text[] = "Hello, Memory Walker! 这是一个测试字符串。";
    printf("1. 遍历字符串:\n");
    printf("   字符串内容: %s\n", text);
    memory_walker(text, strlen(text) + 1, 16); // +1 包含 null 终止符
    
    // 示例2: 遍历一个整数数组
    printf("\n\n2. 遍历整数数组:\n");
    int numbers[] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00, 0x12345678};
    size_t numbers_size = sizeof(numbers);
    printf("   数组大小: %zu 字节 (%zu 个整数)\n", numbers_size, numbers_size / sizeof(int));
    memory_walker(numbers, numbers_size, 16);
    
    // 示例3: 遍历结构体
    printf("\n\n3. 遍历结构体:\n");
    struct SampleStruct {
        int id;
        char name[16];
        float score;
        double value;
    };
    
    struct SampleStruct sample = {
        .id = 1001,
        .name = "Test Struct",
        .score = 95.5f,
        .value = 3.1415926535
    };
    
    printf("   结构体大小: %zu 字节\n", sizeof(sample));
    memory_walker(&sample, sizeof(sample), 16);
    
    // 示例4: 按不同数据类型遍历
    printf("\n\n4. 按数据类型遍历:\n");
    void *data = &sample;
    
    // 访问整数
    printf("   结构体ID (int): %d\n", *(int *)data);
    
    // 访问字符串
    printf("   结构体名称 (char[16]): %s\n", (char *)((char *)data + sizeof(int)));
    
    // 访问浮点数 (跳过int和16字节的char数组)
    char *float_ptr = (char *)data + sizeof(int) + 16;
    printf("   结构体分数 (float): %.2f\n", *(float *)float_ptr);
    
    // 访问双精度浮点数 (注意内存对齐)
    char *double_ptr = float_ptr + sizeof(float);
    // 处理可能的对齐填充
    if ((uintptr_t)double_ptr % 8 != 0) {
        double_ptr += (8 - ((uintptr_t)double_ptr % 8));
    }
    printf("   结构体值 (double): %.10f\n", *(double *)double_ptr);
}

// 高级功能：查找特定字节模式
void find_pattern(const void *start_addr, size_t size, const unsigned char *pattern, size_t pattern_len) {
    const unsigned char *ptr = (const unsigned char *)start_addr;
    const unsigned char *end_ptr = ptr + size - pattern_len + 1;
    
    printf("\n=== 查找字节模式: ===\n");
    printf("模式: ");
    for (size_t i = 0; i < pattern_len; i++) {
        printf("%02x ", pattern[i]);
    }
    printf("\n");
    
    int found = 0;
    for (const unsigned char *current = ptr; current < end_ptr; current++) {
        if (memcmp(current, pattern, pattern_len) == 0) {
            printf("找到匹配于偏移量: 0x%08lx (%lu)\n", 
                   (unsigned long)(current - ptr),
                   (unsigned long)(current - ptr));
            found = 1;
        }
    }
    
    if (!found) {
        printf("未找到匹配的模式\n");
    }
}

int main() {
    printf("内存遍历程序\n");
    printf("============\n");
    
    // 演示安全的内存遍历
    safe_memory_demo();
    
    // 演示模式查找
    printf("\n\n=== 模式查找演示 ===\n");
    char test_data[] = "This is some test data with pattern: ABCDEFGHIJKLMNOP";
    unsigned char pattern[] = {'p', 'a', 't', 't', 'e', 'r', 'n'};
    
    find_pattern(test_data, sizeof(test_data), pattern, sizeof(pattern));
    
    // 交互式内存查看
    printf("\n\n=== 交互式内存查看 ===\n");
    printf("请输入要查看的字符串: ");
    
    char input[256];
    if (fgets(input, sizeof(input), stdin)) {
        // 移除换行符
        input[strcspn(input, "\n")] = 0;
        
        printf("\n您输入的字符串: %s\n", input);
        printf("长度: %zu 字符\n", strlen(input));
        printf("内存大小: %zu 字节 (包含null终止符)\n\n", strlen(input) + 1);
        
        // 让用户选择每行显示多少字节
        int bytes_per_line = 16;
        printf("请输入每行显示的字节数 (默认为16): ");
        char choice[10];
        if (fgets(choice, sizeof(choice), stdin)) {
            int temp = atoi(choice);
            if (temp > 0 && temp <= 32) {
                bytes_per_line = temp;
            }
        }
        
        memory_walker(input, strlen(input) + 1, bytes_per_line);
    }
    
    printf("\n程序结束\n");
    
    return 0;
}