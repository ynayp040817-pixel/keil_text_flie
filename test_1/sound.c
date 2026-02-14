#include <STC89C5xRC.H>

// 定义蜂鸣器引脚
sbit BUZZER = P2^3;

// 更精确的延时函数
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++);
}

// 微秒级延时，更精确
void delay_us(unsigned char us)
{
    while(us--);
}

// 产生指定频率的方波（用于无源蜂鸣器）
void beep_freq(unsigned int freq, unsigned int duration_ms)
{
    unsigned int period_us = 1000000 / freq;  // 周期（微秒）
    unsigned int half_period = period_us / 2;
    unsigned int cycles = (duration_ms * 1000) / period_us;
    unsigned int i;  // 在函数开头声明变量
    
    // 限制最小周期以确保准确性
    if(half_period < 10) half_period = 10;  // 最小10微秒半周期
    
    for(i = 0; i < cycles; i++)
    {
        BUZZER = 1;  // 输出高电平
        delay_us((unsigned char)half_period);
        BUZZER = 0;  // 输出低电平
        delay_us((unsigned char)half_period);
    }
}

// 播放音符
void play_note(unsigned int frequency, unsigned int duration)
{
    beep_freq(frequency, duration);
    delay_ms(100);  // 音符间的间隔稍长一些
}

void main()
{
    // 使用更明显的音阶差异
    unsigned int notes[] = {220, 247, 262, 294, 330, 349, 392};  // 低八度音阶
    unsigned char i;  // 在函数开头声明变量

    while(1)
    {
        // 依次播放七个音阶
        for(i = 0; i < 7; i++)
        {
            // 播放当前音符
            play_note(notes[i], 600);  // 每个音符持续600ms，更容易分辨
        }

        delay_ms(1500);  // 每轮结束后暂停1.5秒
    }
}