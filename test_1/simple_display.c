#include <STC89C5xRC.H>

// 数码管段码定义 (共阴极数码管)
// 段定义: DP-G-F-E-D-C-B-A (P0.7-P0.6-P0.5-P0.4-P0.3-P0.2-P0.1-P0.0)
unsigned char code seg_code[] = {
    0x3F,  // 0 - 00111111
    0x06,  // 1 - 00000110
    0x5B,  // 2 - 01011011
    0x4F,  // 3 - 01001111
    0x66,  // 4 - 01100110
    0x6D,  // 5 - 01101101
    0x7D,  // 6 - 01111101
    0x07,  // 7 - 00000111
    0x7F,  // 8 - 01111111
    0x6F,  // 9 - 01101111
};

// 简单延时函数
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++);
}

// 单个数码管显示函数
void display_digit(unsigned char digit)
{
    if(digit > 9) digit = 0;  // 只显示0-9
    P0 = seg_code[digit];     // 将段码输出到P0口
}

// 主函数 - 简化版
void main()
{
    unsigned char counter = 0;
    
    // 初始化端口
    P0 = 0xFF;  // P0初始化为高电平（所有段熄灭）
    
    while(1)
    {
        // 循环显示0-9
        display_digit(counter % 10);
        delay_ms(1000);  // 每秒切换一个数字
        counter++;
    }
}