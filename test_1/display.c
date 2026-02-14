#include <STC89C5xRC.H>

// 标准段码定义 (共阴极数码管)
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

// 延时函数
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++);
}

void main()
{
    unsigned char counter = 0;

    // 初始化端口
    P0 = 0xFF;  // P0初始化为高电平
    P1 = 0xFF;  // P1初始化为高电平
    P2 = 0xFF;  // P2初始化为高电平
    P3 = 0xFF;  // P3初始化为高电平

    while(1)
    {
        // 根据您的描述，P0口控制段选，P2.7控制位选
        unsigned char display_data = seg_code[counter % 10];
        
        // 设置段选（P0口）
        P0 = display_data;
        
        // 设置位选（P2.7），选中特定的数码管
        P2 = 0xBF;  // P2.7 = 0，选中特定数码管
        
        delay_ms(1000);  // 每秒切换一个数字
        
        counter++;
    }
}