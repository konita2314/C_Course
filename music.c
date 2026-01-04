#include <windows.h>
#include <stdio.h>
#include <math.h>

// 音符频率定义（MIDI音符编号对应频率）
#define C4  261.63  // 60
#define D4  293.66  // 62
#define E4  329.63  // 64
#define F4  349.23  // 65
#define G4  392.00  // 67
#define A4  440.00  // 69
#define B4  493.88  // 71
#define C5  523.25  // 72

// 音符结构体
typedef struct {
    int note;       // MIDI音符编号
    int duration;   // 持续时间（毫秒）
} Note;

// 经典旋律示例：《小星星》
Note little_star[] = {
    {60, 500}, {60, 500}, {72, 500}, {72, 500}, {71, 500}, {71, 500}, {69, 1000},
    {67, 500}, {67, 500}, {65, 500}, {65, 500}, {64, 500}, {64, 500}, {62, 1000},
    {60, 500}, {60, 500}, {72, 500}, {72, 500}, {71, 500}, {71, 500}, {69, 1000},
    {67, 500}, {67, 500}, {65, 500}, {65, 500}, {64, 500}, {64, 500}, {62, 1000}
};

// 根据MIDI音符编号获取频率
double getFrequency(int midiNote) {
    // MIDI音符到频率的转换公式：f = 440 * 2^((n-69)/12)
    return 440.0 * pow(2.0, (midiNote - 69) / 12.0);
}

// Windows下播放单个音符
void playNoteWindows(int midiNote, int duration) {
    double frequency = getFrequency(midiNote);
    
    if (frequency < 37 || frequency > 32767) {
        printf("频率超出范围: %.2f Hz\n", frequency);
        return;
    }
    
    // Windows Beep函数：频率(Hz), 持续时间(ms)
    Beep((DWORD)frequency, (DWORD)duration);
}

// 播放旋律
void playMelodyWindows(Note melody[], int length) {
    printf("开始播放音乐...\n");
    
    for (int i = 0; i < length; i++) {
        printf("播放音符 %d (%.2f Hz), 持续 %d 毫秒\n", 
               melody[i].note, 
               getFrequency(melody[i].note), 
               melody[i].duration);
        
        playNoteWindows(melody[i].note, melody[i].duration);
        
        // 音符之间的短暂间隔
        Sleep(50);
    }
    
    printf("音乐播放结束！\n");
}

int main() {
    int melodyLength = sizeof(little_star) / sizeof(little_star[0]);
    playMelodyWindows(little_star, melodyLength);
    return 0;
}