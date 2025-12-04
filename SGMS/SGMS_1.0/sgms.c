#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

#define MAX_STUDENTS 1000
#define MAX_NAME_LEN 50
#define MAX_ID_LEN 20
#define MAX_CMD_LEN 256
#define SETTINGS_FILE "settings.bin"
#define DATA_FILE "data.bin"
#define DEFAULT_PASS_SCORE 60
#define DEFAULT_ENCODING 0 // 0:UTF-8, 1:GBK

// 编码类型
typedef enum
{
    ENCODING_UTF8 = 0,
    ENCODING_GBK = 1
} EncodingType;

// 学生结构体
typedef struct
{
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    int score;
    int rank;
} Student;

// 设置结构体
typedef struct
{
    int pass_score;
    EncodingType encoding;
    int auto_save;     // 自动保存: 0-关闭, 1-开启
    int max_students;  // 最大学生数
    int version_major; // 主版本号
    int version_minor; // 次版本号
} Settings;

// 全局变量
Student students[MAX_STUDENTS];
int student_count = 0;
Settings settings;

// 函数声明
void init_settings();
void save_settings();
void load_settings();
void load_data();
void save_data();
void auto_save();
void clear_input_buffer();
void print_welcome();
void print_help();
void print_help_command(const char *command);
void print_settings();
void settings_menu();
void settings_command(char *args);
void set_pass_score(char *args);
void set_encoding(char *args);
void set_auto_save(char *args);
void add_profile();
void add_profile_args(char *args);
void edit_profile(char *args);
void delete_profile(char *args);
void find_profile(char *args);
void find_with_wildcard(const char *pattern, bool by_id);
int wildcard_match(const char *pattern, const char *text);
void list_total(char *args);
void calculate_stats();
void show_average();
void show_passed_info();
void sort_by_id();
void sort_by_score();
void bubble_sort_students(Student arr[], int n, bool by_score);
int find_student_by_id(const char *id);
int find_student_by_name(const char *name);
void print_student_table_header();
void print_student_row(Student *s);
void execute_command(char *command);
char *trim_whitespace(char *str);
void print_error(const char *message);
void print_success(const char *message);
void print_warning(const char *message);
void update_ranking();
void export_to_text(const char *filename);
void import_from_text(const char *filename);
void backup_data();
void restore_backup();

int main()
{
    // 设置本地化，支持中文
    setlocale(LC_ALL, "");

    char command[MAX_CMD_LEN];

    // 初始化
    load_settings();
    load_data();
    print_welcome();

    // 主循环
    while (1)
    {
        printf("\n> ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
        }

        // 移除换行符
        command[strcspn(command, "\n")] = 0;

        // 跳过空命令
        if (strlen(command) == 0)
        {
            continue;
        }

        // 处理命令
        execute_command(command);

        // 自动保存
        if (settings.auto_save)
        {
            auto_save();
        }
    }

    return 0;
}

// 初始化设置
void init_settings()
{
    settings.pass_score = DEFAULT_PASS_SCORE;
    settings.encoding = ENCODING_UTF8;
    settings.auto_save = 1; // 默认开启自动保存
    settings.max_students = MAX_STUDENTS;
    settings.version_major = 1;
    settings.version_minor = 1;
}

// 保存设置到文件
void save_settings()
{
    FILE *file = fopen(SETTINGS_FILE, "wb");
    if (file)
    {
        fwrite(&settings, sizeof(Settings), 1, file);
        fclose(file);
    }
}

// 从文件加载设置
void load_settings()
{
    FILE *file = fopen(SETTINGS_FILE, "rb");
    if (file)
    {
        fread(&settings, sizeof(Settings), 1, file);
        fclose(file);
        printf("已加载设置（版本：%d.%d）\n", settings.version_major, settings.version_minor);
    }
    else
    {
        printf("欢迎使用学生成绩管理系统 v1.1\n");
        printf("以下为设置向导：\n");
        init_settings();
        settings_menu(); // 初次启动进入设置向导
    }
}

// 加载学生数据
void load_data()
{
    FILE *file = fopen(DATA_FILE, "rb");
    if (file)
    {
        fread(&student_count, sizeof(int), 1, file);
        if (student_count > MAX_STUDENTS)
        {
            student_count = MAX_STUDENTS;
        }
        fread(students, sizeof(Student), student_count, file);
        fclose(file);
        printf("已加载 %d 条学生记录\n", student_count);
    }
    else
    {
        printf("未找到数据文件，创建新数据库\n");
        student_count = 0;
    }
}

// 保存学生数据
void save_data()
{
    FILE *file = fopen(DATA_FILE, "wb");
    if (file)
    {
        fwrite(&student_count, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), student_count, file);
        fclose(file);
    }
}

// 自动保存
void auto_save()
{
    static int save_counter = 0;
    save_counter++;
    if (save_counter >= 10)
    { // 每10次操作自动保存
        save_data();
        save_counter = 0;
    }
}

// 清空输入缓冲区
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// 打印欢迎信息
void print_welcome()
{
    const char *encoding_str = (settings.encoding == ENCODING_UTF8) ? "UTF-8" : "GBK";

    printf("==================================================\n");
    printf("   学生成绩管理系统 v%d.%d\n", settings.version_major, settings.version_minor);
    printf("   编码：%s | 及格线：%d | 自动保存：%s\n",
           encoding_str,
           settings.pass_score,
           settings.auto_save ? "开启" : "关闭");
    printf("   输入 'help' 获取帮助\n");
    printf("   输入 'exit' 退出程序\n");
    printf("==================================================\n");
}

// 打印帮助信息
void print_help()
{
    printf("\n命令大全：\n");
    printf("==================================================\n");
    printf("  exit                 - 退出程序\n");
    printf("  help [命令]          - 显示帮助\n");
    printf("  set                  - 进入设置菜单\n");
    printf("  set <命令> [参数]    - 直接设置\n");
    printf("  addprofile           - 添加学生（交互式）\n");
    printf("  addprofile <学号> <姓名> <分数> - 直接添加\n");
    printf("  editprofile /num <学号> <新分数> - 按学号修改\n");
    printf("  editprofile /name <姓名> <新分数> - 按姓名修改\n");
    printf("  delete /num <学号>   - 按学号删除\n");
    printf("  delete /name <姓名>  - 按姓名删除\n");
    printf("  find /num <学号>     - 按学号查找（支持通配符*）\n");
    printf("  find /name <姓名>    - 按姓名查找（支持通配符*）\n");
    printf("  total /num          - 按学号排序显示\n");
    printf("  total /score        - 按成绩排序显示\n");
    printf("  average             - 显示平均分\n");
    printf("  ispassed            - 显示及格信息\n");
    printf("  size                - 显示学生总数\n");
    printf("  backup              - 备份数据\n");
    printf("  restore             - 恢复备份\n");
    printf("  export <文件名>     - 导出为文本文件\n");
    printf("  import <文件名>     - 从文本文件导入\n");
    printf("==================================================\n");
}

// 打印特定命令的帮助
void print_help_command(const char *command)
{
    if (strcmp(command, "exit") == 0)
    {
        printf("exit - 退出学生成绩管理系统\n");
    }
    else if (strcmp(command, "help") == 0)
    {
        printf("help [命令] - 显示帮助信息\n");
        printf("  不带参数：显示所有命令\n");
        printf("  带参数：显示特定命令的详细帮助\n");
    }
    else if (strcmp(command, "set") == 0)
    {
        printf("set - 系统设置\n");
        printf("  用法1: set （进入交互式设置模式）\n");
        printf("  用法2: set <命令> [参数] （直接设置）\n");
        printf("  可用命令：\n");
        printf("    passscore <分数>   - 设置及格分数线\n");
        printf("    encoding <类型>    - 设置编码（utf8/gbk）\n");
        printf("    autosave <状态>    - 设置自动保存（on/off）\n");
        printf("    show               - 显示当前设置\n");
        printf("    reset              - 恢复默认设置\n");
    }
    else if (strcmp(command, "addprofile") == 0)
    {
        printf("addprofile - 添加学生记录\n");
        printf("  用法1: addprofile （进入交互式输入模式）\n");
        printf("  用法2: addprofile <学号> <姓名> <分数>\n");
    }
    else if (strcmp(command, "editprofile") == 0)
    {
        printf("editprofile - 修改学生成绩\n");
        printf("  用法1: editprofile /num <学号> <新分数>\n");
        printf("  用法2: editprofile /name <姓名> <新分数>\n");
    }
    else if (strcmp(command, "delete") == 0)
    {
        printf("delete - 删除学生记录\n");
        printf("  用法1: delete /num <学号>\n");
        printf("  用法2: delete /name <姓名>\n");
    }
    else if (strcmp(command, "find") == 0)
    {
        printf("find - 查找学生记录\n");
        printf("  用法1: find /num <学号> （支持通配符*）\n");
        printf("  用法2: find /name <姓名> （支持通配符*）\n");
        printf("  通配符示例：\n");
        printf("    find /num 200*     - 查找所有以200开头的学号\n");
        printf("    find /num *123*    - 查找所有包含123的学号\n");
        printf("    find /name 张*     - 查找所有姓张的学生\n");
    }
    else if (strcmp(command, "total") == 0)
    {
        printf("total - 显示成绩表\n");
        printf("  用法1: total /num （按学号排序）\n");
        printf("  用法2: total /score （按成绩排序）\n");
    }
    else if (strcmp(command, "average") == 0)
    {
        printf("average - 显示平均分\n");
    }
    else if (strcmp(command, "ispassed") == 0)
    {
        printf("ispassed - 显示及格人数和及格率\n");
    }
    else if (strcmp(command, "size") == 0)
    {
        printf("size - 显示学生总数\n");
    }
    else if (strcmp(command, "backup") == 0)
    {
        printf("backup - 备份当前数据\n");
    }
    else if (strcmp(command, "restore") == 0)
    {
        printf("restore - 从备份恢复数据\n");
    }
    else if (strcmp(command, "export") == 0)
    {
        printf("export <文件名> - 导出数据到文本文件\n");
    }
    else if (strcmp(command, "import") == 0)
    {
        printf("import <文件名> - 从文本文件导入数据\n");
    }
    else
    {
        printf("未找到命令 '%s' 的帮助信息\n", command);
    }
}

// 打印当前设置
void print_settings()
{
    const char *encoding_str = (settings.encoding == ENCODING_UTF8) ? "UTF-8" : "GBK";
    const char *autosave_str = settings.auto_save ? "开启" : "关闭";

    printf("\n当前系统设置：\n");
    printf("==================================================\n");
    printf("  版本：           v%d.%d\n", settings.version_major, settings.version_minor);
    printf("  及格分数线：     %d\n", settings.pass_score);
    printf("  字符编码：       %s\n", encoding_str);
    printf("  自动保存：       %s\n", autosave_str);
    printf("  最大学生数：     %d\n", settings.max_students);
    printf("  当前学生数：     %d\n", student_count);
    printf("==================================================\n");
}

// 设置菜单
void settings_menu()
{
    char command[MAX_CMD_LEN];

    printf("\n|设置模式===========================================|\n");
    printf("|输入命令进行设置，输入 'exit' 退出设置模式        |\n");
    printf("|输入 'show' 显示当前设置                          |\n");
    printf("|输入 'reset' 恢复默认设置                         |\n");
    printf("|==================================================|\n");

    while (1)
    {
        printf("\nset> ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
        }

        command[strcspn(command, "\n")] = 0;

        if (strlen(command) == 0)
        {
            continue;
        }

        if (strcmp(command, "exit") == 0)
        {
            break;
        }

        settings_command(command);
    }

    printf("已退出设置模式\n");
    save_settings();
}

// 设置命令
void settings_command(char *args)
{
    char cmd[50];
    char param[100];

    if (sscanf(args, "%s %[^\n]", cmd, param) < 1)
    {
        printf("错误：需要命令\n");
        return;
    }

    if (strcmp(cmd, "show") == 0)
    {
        print_settings();
    }
    else if (strcmp(cmd, "reset") == 0)
    {
        printf("是否恢复默认设置？(Y/N) > ");
        char confirm;
        scanf(" %c", &confirm);
        clear_input_buffer();

        if (confirm == 'Y' || confirm == 'y')
        {
            init_settings();
            save_settings();
            printf("已恢复默认设置\n");
            print_settings();
        }
        else
        {
            printf("已取消\n");
        }
    }
    else if (strcmp(cmd, "passscore") == 0)
    {
        set_pass_score(param);
    }
    else if (strcmp(cmd, "encoding") == 0)
    {
        set_encoding(param);
    }
    else if (strcmp(cmd, "autosave") == 0)
    {
        set_auto_save(param);
    }
    else
    {
        printf("未知的设置命令：%s\n", cmd);
        printf("可用命令：show, reset, passscore, encoding, autosave\n");
    }
}

// 设置及格分数线
void set_pass_score(char *args)
{
    int new_score = atoi(args);

    if (new_score < 0 || new_score > 100)
    {
        printf("错误：及格分数线必须在0-100之间\n");
        return;
    }

    if (new_score == settings.pass_score)
    {
        printf("及格分数线已经是 %d。\n", new_score);
        return;
    }

    printf("是否将及格分数线从 %d 改为 %d？\n", settings.pass_score, new_score);
    printf("（键入Y或N以接受或否定）> ");

    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm == 'Y' || confirm == 'y')
    {
        int old_score = settings.pass_score;
        settings.pass_score = new_score;
        save_settings();
        printf("已修改及格分数线：%d -> %d\n", old_score, new_score);
    }
    else
    {
        printf("已取消\n");
    }
}

// 设置编码
void set_encoding(char *args)
{
    const char *current = (settings.encoding == ENCODING_UTF8) ? "UTF-8" : "GBK";
    const char *new_encoding = "未知";
    EncodingType new_type;

    if (strcmp(args, "utf8") == 0 || strcmp(args, "UTF-8") == 0)
    {
        new_type = ENCODING_UTF8;
        new_encoding = "UTF-8";
    }
    else if (strcmp(args, "gbk") == 0 || strcmp(args, "GBK") == 0)
    {
        new_type = ENCODING_GBK;
        new_encoding = "GBK";
    }
    else
    {
        printf("错误：编码类型必须是 'utf8' 或 'gbk'\n");
        return;
    }

    if (new_type == settings.encoding)
    {
        printf("字符编码已经是 %s。\n", new_encoding);
        return;
    }

    printf("是否将字符编码从 %s 改为 %s？\n", current, new_encoding);
    printf("（注意：更改编码可能需要重新启动程序才能生效）\n");
    printf("（键入Y或N以接受或否定）> ");

    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm == 'Y' || confirm == 'y')
    {
        settings.encoding = new_type;
        save_settings();
        printf("已修改字符编码：%s -> %s\n", current, new_encoding);
        printf("请重新启动程序以使更改生效\n");
    }
    else
    {
        printf("已取消\n");
    }
}

// 设置自动保存
void set_auto_save(char *args)
{
    int new_state;
    const char *current = settings.auto_save ? "开启" : "关闭";
    const char *new_state_str;

    if (strcmp(args, "on") == 0 || strcmp(args, "1") == 0 || strcmp(args, "开启") == 0)
    {
        new_state = 1;
        new_state_str = "开启";
    }
    else if (strcmp(args, "off") == 0 || strcmp(args, "0") == 0 || strcmp(args, "关闭") == 0)
    {
        new_state = 0;
        new_state_str = "关闭";
    }
    else
    {
        printf("错误：状态必须是 'on' 或 'off'\n");
        return;
    }

    if (new_state == settings.auto_save)
    {
        printf("自动保存已经是 %s。\n", new_state_str);
        return;
    }

    printf("是否将自动保存从 %s 改为 %s？\n", current, new_state_str);
    printf("（键入Y或N以接受或否定）> ");

    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm == 'Y' || confirm == 'y')
    {
        settings.auto_save = new_state;
        save_settings();
        printf("已修改自动保存：%s -> %s\n", current, new_state_str);
    }
    else
    {
        printf("已取消\n");
    }
}

// 交互式添加学生
void add_profile()
{
    if (student_count >= MAX_STUDENTS)
    {
        printf("错误：数据库已满，最多支持 %d 名学生\n", MAX_STUDENTS);
        return;
    }

    Student new_student;

    printf("请输入学号：");
    fgets(new_student.id, sizeof(new_student.id), stdin);
    new_student.id[strcspn(new_student.id, "\n")] = 0;

    printf("请输入姓名：");
    fgets(new_student.name, sizeof(new_student.name), stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;

    printf("请输入成绩：");
    char score_str[20];
    fgets(score_str, sizeof(score_str), stdin);
    new_student.score = atoi(score_str);

    printf("\n确认添加学生？\n");
    printf("学号：%s\n", new_student.id);
    printf("姓名：%s\n", new_student.name);
    printf("成绩：%d\n", new_student.score);
    printf("（键入Y或N以接受或否定）> ");

    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm == 'Y' || confirm == 'y')
    {
        students[student_count] = new_student;
        student_count++;
        save_data();
        printf("已成功添加学生\n");
    }
    else
    {
        printf("已取消添加\n");
    }
}

// 通过参数添加学生
void add_profile_args(char *args)
{
    if (student_count >= MAX_STUDENTS)
    {
        printf("错误：数据库已满\n");
        return;
    }

    char id[MAX_ID_LEN], name[MAX_NAME_LEN];
    int score;

    if (sscanf(args, "%s %s %d", id, name, &score) != 3)
    {
        printf("错误：参数格式不正确\n");
        printf("正确格式：addprofile <学号> <姓名> <分数>\n");
        return;
    }

    // 检查学号是否已存在
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
        {
            printf("错误：学号 '%s' 已存在\n", id);
            return;
        }
    }

    Student new_student;
    strcpy(new_student.id, id);
    strcpy(new_student.name, name);
    new_student.score = score;

    students[student_count] = new_student;
    student_count++;
    save_data();

    printf("已成功添加学生：%s (%s) - %d分\n", name, id, score);
}

// 编辑学生成绩
void edit_profile(char *args)
{
    char type[10], identifier[MAX_ID_LEN];
    int new_score;

    if (sscanf(args, "%s %s %d", type, identifier, &new_score) != 3)
    {
        printf("错误：参数格式不正确\n");
        printf("正确格式：editprofile /num <学号> <新分数> 或 editprofile /name <姓名> <新分数>\n");
        return;
    }

    int index = -1;
    if (strcmp(type, "/num") == 0)
    {
        index = find_student_by_id(identifier);
    }
    else if (strcmp(type, "/name") == 0)
    {
        index = find_student_by_name(identifier);
    }
    else
    {
        printf("错误：类型必须是 /num 或 /name\n");
        return;
    }

    if (index == -1)
    {
        if (strcmp(type, "/num") == 0)
        {
            printf("错误：未找到学号为 '%s' 的学生\n", identifier);
        }
        else
        {
            printf("错误：未找到姓名为 '%s' 的学生\n", identifier);
        }
        return;
    }

    int old_score = students[index].score;
    printf("是否将学生 %s (%s) 的成绩从 %d 改为 %d？\n",
           students[index].name, students[index].id, old_score, new_score);
    printf("（键入Y或N以接受或否定）> ");

    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm == 'Y' || confirm == 'y')
    {
        students[index].score = new_score;
        save_data();
        printf("已修改\n");
    }
    else
    {
        printf("已取消\n");
    }
}

// 删除学生
void delete_profile(char *args)
{
    char type[10], identifier[MAX_ID_LEN];

    if (sscanf(args, "%s %s", type, identifier) != 2)
    {
        printf("错误：参数格式不正确\n");
        printf("正确格式：delete /num <学号> 或 delete /name <姓名>\n");
        return;
    }

    int index = -1;
    if (strcmp(type, "/num") == 0)
    {
        index = find_student_by_id(identifier);
    }
    else if (strcmp(type, "/name") == 0)
    {
        index = find_student_by_name(identifier);
    }
    else
    {
        printf("错误：类型必须是 /num 或 /name\n");
        return;
    }

    if (index == -1)
    {
        if (strcmp(type, "/num") == 0)
        {
            printf("错误：未找到学号为 '%s' 的学生\n", identifier);
        }
        else
        {
            printf("错误：未找到姓名为 '%s' 的学生\n", identifier);
        }
        return;
    }

    printf("确认删除学生 %s (%s)？\n", students[index].name, students[index].id);
    printf("（键入Y或N以接受或否定）> ");

    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm == 'Y' || confirm == 'y')
    {
        // 将最后一个元素移动到删除的位置
        students[index] = students[student_count - 1];
        student_count--;
        save_data();
        printf("已删除\n");
    }
    else
    {
        printf("已取消\n");
    }
}

// 通配符匹配函数
int wildcard_match(const char *pattern, const char *text)
{
    if (*pattern == '\0' && *text == '\0')
    {
        return 1;
    }

    if (*pattern == '*')
    {
        // 跳过连续的*
        while (*pattern == '*')
        {
            pattern++;
        }

        if (*pattern == '\0')
        {
            return 1; // 模式以*结尾，匹配所有
        }

        // 递归匹配
        while (*text != '\0')
        {
            if (wildcard_match(pattern, text))
            {
                return 1;
            }
            text++;
        }

        return wildcard_match(pattern, text);
    }

    if (*text != '\0' && (*pattern == '?' || *pattern == *text))
    {
        return wildcard_match(pattern + 1, text + 1);
    }

    return 0;
}

// 使用通配符查找
void find_with_wildcard(const char *pattern, bool by_id)
{
    int found_count = 0;

    printf("\n|找到以下结果========================================|\n");
    print_student_table_header();

    for (int i = 0; i < student_count; i++)
    {
        int match = 0;

        if (by_id)
        {
            match = wildcard_match(pattern, students[i].id);
        }
        else
        {
            match = wildcard_match(pattern, students[i].name);
        }

        if (match)
        {
            students[i].rank = 0; // 通配符查找不显示排名
            print_student_row(&students[i]);
            found_count++;
        }
    }

    if (found_count == 0)
    {
        printf("|未找到匹配的结果                                     |\n");
    }
    printf("|====================================================|\n");
    printf("共找到 %d 条记录\n", found_count);
}

// 查找学生
void find_profile(char *args)
{
    char type[10], identifier[MAX_ID_LEN];

    if (sscanf(args, "%s %s", type, identifier) != 2)
    {
        printf("错误：参数格式不正确\n");
        printf("正确格式：find /num <学号> 或 find /name <姓名>\n");
        return;
    }

    // 检查是否包含通配符
    int has_wildcard = 0;
    for (int i = 0; identifier[i] != '\0'; i++)
    {
        if (identifier[i] == '*' || identifier[i] == '?')
        {
            has_wildcard = 1;
            break;
        }
    }

    if (has_wildcard)
    {
        if (strcmp(type, "/num") == 0)
        {
            find_with_wildcard(identifier, true);
        }
        else if (strcmp(type, "/name") == 0)
        {
            find_with_wildcard(identifier, false);
        }
        else
        {
            printf("错误：类型必须是 /num 或 /name\n");
        }
        return;
    }

    // 精确查找
    int index = -1;
    if (strcmp(type, "/num") == 0)
    {
        index = find_student_by_id(identifier);
    }
    else if (strcmp(type, "/name") == 0)
    {
        index = find_student_by_name(identifier);
    }
    else
    {
        printf("错误：类型必须是 /num 或 /name\n");
        return;
    }

    if (index == -1)
    {
        if (strcmp(type, "/num") == 0)
        {
            printf("未找到学号为 '%s' 的学生\n", identifier);
        }
        else
        {
            printf("未找到姓名为 '%s' 的学生\n", identifier);
        }
        return;
    }

    // 计算排名
    sort_by_score();
    int rank = 1;
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].id, identifier) == 0)
        {
            break;
        }
        rank++;
    }

    printf("\n|找到以下结果========================================|\n");
    print_student_table_header();
    students[index].rank = rank;
    print_student_row(&students[index]);
    printf("|====================================================|\n");
}

// 显示成绩表
void list_total(char *args)
{
    if (student_count == 0)
    {
        printf("数据库中暂无学生记录\n");
        return;
    }

    if (strcmp(args, "/num") == 0)
    {
        sort_by_id();
        printf("\n|按学号排序的成绩表====================================|\n");
    }
    else if (strcmp(args, "/score") == 0)
    {
        sort_by_score();
        update_ranking();
        printf("\n|按成绩排序的成绩表====================================|\n");
    }
    else
    {
        printf("错误：参数必须是 /num 或 /score\n");
        return;
    }

    print_student_table_header();
    for (int i = 0; i < student_count; i++)
    {
        print_student_row(&students[i]);
    }
    printf("|====================================================|\n");
}

// 计算统计信息
void calculate_stats()
{
    // 此函数当前用于准备数据，留待扩展
}

// 更新排名
void update_ranking()
{
    for (int i = 0; i < student_count; i++)
    {
        students[i].rank = i + 1;
    }
}

// 显示平均分
void show_average()
{
    if (student_count == 0)
    {
        printf("数据库中暂无学生记录\n");
        return;
    }

    int sum = 0;
    for (int i = 0; i < student_count; i++)
    {
        sum += students[i].score;
    }

    float average = (float)sum / student_count;
    printf("平均分：%.2f\n", average);

    // 显示分数段分布
    int excellent = 0, good = 0, medium = 0, pass = 0, fail = 0;
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].score >= 90)
            excellent++;
        else if (students[i].score >= 80)
            good++;
        else if (students[i].score >= 70)
            medium++;
        else if (students[i].score >= settings.pass_score)
            pass++;
        else
            fail++;
    }

    printf("分数段分布：\n");
    printf("  优秀(90-100)：%d人 (%.1f%%)\n", excellent, (float)excellent / student_count * 100);
    printf("  良好(80-89)： %d人 (%.1f%%)\n", good, (float)good / student_count * 100);
    printf("  中等(70-79)： %d人 (%.1f%%)\n", medium, (float)medium / student_count * 100);
    printf("  及格(%d-69)： %d人 (%.1f%%)\n", settings.pass_score, pass, (float)pass / student_count * 100);
    printf("  不及格：      %d人 (%.1f%%)\n", fail, (float)fail / student_count * 100);
}

// 显示及格信息
void show_passed_info()
{
    if (student_count == 0)
    {
        printf("数据库中暂无学生记录\n");
        return;
    }

    int passed_count = 0;
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].score >= settings.pass_score)
        {
            passed_count++;
        }
    }

    float pass_rate = (float)passed_count / student_count * 100;
    printf("及格分数线：%d\n", settings.pass_score);
    printf("及格人数：%d / %d\n", passed_count, student_count);
    printf("及格率：%.2f%%\n", pass_rate);

    // 显示最高分和最低分
    int max_score = -1, min_score = 101;
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].score > max_score)
            max_score = students[i].score;
        if (students[i].score < min_score)
            min_score = students[i].score;
    }

    printf("最高分：%d\n", max_score);
    printf("最低分：%d\n", min_score);
}

// 按学号排序
void sort_by_id()
{
    bubble_sort_students(students, student_count, false);
}

// 按成绩排序
void sort_by_score()
{
    bubble_sort_students(students, student_count, true);
}

// 冒泡排序学生数组
void bubble_sort_students(Student arr[], int n, bool by_score)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            bool should_swap = false;

            if (by_score)
            {
                // 按成绩降序排序
                if (arr[j].score < arr[j + 1].score)
                {
                    should_swap = true;
                }
            }
            else
            {
                // 按学号升序排序
                if (strcmp(arr[j].id, arr[j + 1].id) > 0)
                {
                    should_swap = true;
                }
            }

            if (should_swap)
            {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 按学号查找学生
int find_student_by_id(const char *id)
{
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 按姓名查找学生
int find_student_by_name(const char *name)
{
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 打印学生表头
void print_student_table_header()
{
    printf("|%-20s|%-10s|%-6s|%-5s|\n",
           "姓名", "学号", "成绩", "排名");
    printf("|--------------------|----------|------|-----|\n");
}

// 打印学生行
void print_student_row(Student *s)
{
    printf("|%-20s|%-10s|%-6d|%-5d|\n",
           s->name, s->id, s->score, s->rank);
}

// 备份数据
void backup_data()
{
    char filename[100];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    strftime(filename, sizeof(filename), "backup_%Y%m%d_%H%M%S.bin", tm_info);

    FILE *src = fopen(DATA_FILE, "rb");
    FILE *dst = fopen(filename, "wb");

    if (src && dst)
    {
        int count;
        fread(&count, sizeof(int), 1, src);
        fwrite(&count, sizeof(int), 1, dst);

        Student s;
        for (int i = 0; i < count; i++)
        {
            fread(&s, sizeof(Student), 1, src);
            fwrite(&s, sizeof(Student), 1, dst);
        }

        fclose(src);
        fclose(dst);
        printf("数据已备份到：%s\n", filename);
    }
    else
    {
        printf("备份失败\n");
    }
}

// 恢复备份
void restore_backup()
{
    printf("请输入备份文件名：");
    char filename[100];
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    printf("确认从备份文件 %s 恢复数据？(Y/N) > ", filename);
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm != 'Y' && confirm != 'y')
    {
        printf("已取消\n");
        return;
    }

    FILE *file = fopen(filename, "rb");
    if (file)
    {
        fread(&student_count, sizeof(int), 1, file);
        if (student_count > MAX_STUDENTS)
        {
            student_count = MAX_STUDENTS;
        }
        fread(students, sizeof(Student), student_count, file);
        fclose(file);

        save_data();
        printf("已从备份恢复 %d 条记录\n", student_count);
    }
    else
    {
        printf("错误：无法打开备份文件\n");
    }
}

// 导出为文本文件
void export_to_text(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("错误：无法创建文件\n");
        return;
    }

    fprintf(file, "学生成绩表\n");
    fprintf(file, "生成时间：%s", ctime(&(time_t){time(NULL)}));
    fprintf(file, "==================================================\n");
    fprintf(file, "%-20s %-10s %-6s %-5s\n", "姓名", "学号", "成绩", "排名");
    fprintf(file, "--------------------------------------------------\n");

    sort_by_score();
    update_ranking();

    for (int i = 0; i < student_count; i++)
    {
        fprintf(file, "%-20s %-10s %-6d %-5d\n",
                students[i].name, students[i].id, students[i].score, students[i].rank);
    }

    fprintf(file, "==================================================\n");
    fprintf(file, "总计：%d 名学生\n", student_count);

    fclose(file);
    printf("数据已导出到：%s\n", filename);
}

// 从文本文件导入
void import_from_text(const char *filename)
{
    printf("警告：这将覆盖当前数据！是否继续？(Y/N) > ");
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm != 'Y' && confirm != 'y')
    {
        printf("已取消\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("错误：无法打开文件\n");
        return;
    }

    char line[256];
    student_count = 0;

    // 跳过表头
    for (int i = 0; i < 4; i++)
    {
        fgets(line, sizeof(line), file);
    }

    while (fgets(line, sizeof(line), file) && student_count < MAX_STUDENTS)
    {
        if (strstr(line, "===="))
            break; // 遇到分隔符停止

        Student s;
        if (sscanf(line, "%s %s %d %d", s.name, s.id, &s.score, &s.rank) == 4)
        {
            students[student_count++] = s;
        }
    }

    fclose(file);
    save_data();
    printf("已从文本文件导入 %d 条记录\n", student_count);
}

// 执行命令
void execute_command(char *command)
{
    char cmd[MAX_CMD_LEN];
    char args[MAX_CMD_LEN] = "";

    // 分离命令和参数
    sscanf(command, "%s %[^\n]", cmd, args);

    if (strcmp(cmd, "exit") == 0)
    {
        printf("保存数据并退出...\n");
        save_data();
        exit(0);
    }
    else if (strcmp(cmd, "help") == 0)
    {
        if (strlen(args) > 0)
        {
            print_help_command(args);
        }
        else
        {
            print_help();
        }
    }
    else if (strcmp(cmd, "set") == 0)
    {
        if (strlen(args) == 0)
        {
            settings_menu();
        }
        else
        {
            settings_command(args);
        }
    }
    else if (strcmp(cmd, "addprofile") == 0)
    {
        if (strlen(args) == 0)
        {
            add_profile();
        }
        else
        {
            add_profile_args(args);
        }
    }
    else if (strcmp(cmd, "editprofile") == 0)
    {
        if (strlen(args) == 0)
        {
            printf("错误：需要参数\n");
            printf("用法：editprofile /num <学号> <新分数> 或 editprofile /name <姓名> <新分数>\n");
        }
        else
        {
            edit_profile(args);
        }
    }
    else if (strcmp(cmd, "delete") == 0)
    {
        if (strlen(args) == 0)
        {
            printf("错误：需要参数\n");
            printf("用法：delete /num <学号> 或 delete /name <姓名>\n");
        }
        else
        {
            delete_profile(args);
        }
    }
    else if (strcmp(cmd, "find") == 0)
    {
        if (strlen(args) == 0)
        {
            printf("错误：需要参数\n");
            printf("用法：find /num <学号> 或 find /name <姓名>\n");
        }
        else
        {
            find_profile(args);
        }
    }
    else if (strcmp(cmd, "total") == 0)
    {
        if (strlen(args) == 0)
        {
            printf("错误：需要参数\n");
            printf("用法：total /num 或 total /score\n");
        }
        else
        {
            list_total(args);
        }
    }
    else if (strcmp(cmd, "average") == 0)
    {
        show_average();
    }
    else if (strcmp(cmd, "ispassed") == 0)
    {
        show_passed_info();
    }
    else if (strcmp(cmd, "size") == 0)
    {
        printf("学生总数：%d\n", student_count);
    }
    else if (strcmp(cmd, "backup") == 0)
    {
        backup_data();
    }
    else if (strcmp(cmd, "restore") == 0)
    {
        restore_backup();
    }
    else if (strcmp(cmd, "export") == 0)
    {
        if (strlen(args) == 0)
        {
            printf("错误：需要指定文件名\n");
            printf("用法：export <文件名>\n");
        }
        else
        {
            export_to_text(args);
        }
    }
    else if (strcmp(cmd, "import") == 0)
    {
        if (strlen(args) == 0)
        {
            printf("错误：需要指定文件名\n");
            printf("用法：import <文件名>\n");
        }
        else
        {
            import_from_text(args);
        }
    }
    else
    {
        printf("错误：未找到命令 \"%s\"，请检查拼写。\n", cmd);
        printf("输入 'help' 查看可用命令\n");
    }
}

// 去除字符串首尾空白
char *trim_whitespace(char *str)
{
    char *end;

    // 去除前导空白
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    // 去除尾部空白
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // 添加终止符
    *(end + 1) = 0;

    return str;
}

// 打印错误信息
void print_error(const char *message)
{
    printf("错误：%s\n", message);
}

// 打印成功信息
void print_success(const char *message)
{
    printf("成功：%s\n", message);
}

// 打印警告信息
void print_warning(const char *message)
{
    printf("警告：%s\n", message);
}