#include <STC89C5xRC.H>  // 适配你的STC89C5x系列单片机

// 定义锁存引脚（和你的硬件完全对应）
sbit seg_lock = P2^6;  // 段选锁存引脚（P2.6/DULA）
sbit bit_lock = P2^7;  // 位选锁存引脚（P2.7/WELA）

// 共阴极数码管段码表（0-9，直接对应P0口输出）
unsigned char seg_code[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

// 固定位码（只选通1个显示位，比如第1位，共阴极低电平有效）
#define BIT_CODE 0x7F  // 如果你要选其他位，改这个值即可（比如0xBF对应第2位）

// 延时函数（ms级，晶振11.0592MHz，用于控制数字停留时间）
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = ms; i > 0; i--)
        for(j = 114; j > 0; j--);
}

void main(void) {
    unsigned char num = 0;  // 用于循环0-9的变量
    seg_lock = 0;bit_lock = 1;
    P0 = BIT_CODE;
    bit_lock = 0;
    while(1) {  // 无限循环
        seg_lock = 1;

        P0 = seg_code[num];  // P0口输出0-9对应的段码

        // 第三步：数字停留500ms，然后切换下一个数字
        delay_ms(1000);
        num++;               // 数字+1
        if(num > 9) {        // 超过9则重置为0，循环
            num = 0;
        }
    }
}