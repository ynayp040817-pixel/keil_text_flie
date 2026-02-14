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

// 延时函数
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++);
}

// 主函数 - 8位数码管流水显示
void main()
{
    unsigned char position = 0;  // 当前显示位置
    unsigned char digit = 0;     // 当前显示的数字
    
    // 初始化端口
    P0 = 0x00;  // 段码关闭
    P2 = 0xFF;  // 位选关闭（假设P2控制位选，低电平选中数码管）
    
    while(1)
    {
        // 在指定位置显示数字
        P0 = seg_code[digit];      // 输出段码到P0
        P2 = ~(1 << position);     // 选中第position个数码管（假设低电平选中）
        
        delay_ms(500);             // 显示一段时间
        
        // 移动到下一个位置
        position++;
        if(position >= 8)          // 8个数码管循环
        {
            position = 0;
            digit++;               // 更换显示的数字
            if(digit > 9) digit = 0;  // 数字0-9循环
        }
        
        // 关闭显示，避免拖影
        P0 = 0x00;
        P2 = 0xFF;
        delay_ms(1);              // 短暂消隐时间
    }
}