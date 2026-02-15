#include <STC89C5xRC.H>  // 适配你的STC89C5x系列单片机

// 定义锁存引脚（和你的硬件完全对应）
sbit seg_lock = P2^6;  // 段选锁存引脚（P2.6/DULA）
sbit bit_lock = P2^7;  // 位选锁存引脚（P2.7/WELA）

// 共阴极数码管段码表（0-9，直接对应P0口输出）
unsigned char seg_code[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

// 延时函数（ms级，晶振11.0592MHz，用于控制数字停留时间）
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = ms; i > 0; i--)
        for(j = 114; j > 0; j--);
}

// 将数字分解为各位数字
void get_digits(unsigned long num, unsigned char *digits) {
    unsigned char i;
    for(i = 0; i < 8; i++) {
        digits[7-i] = num % 10;  // 从个位开始提取
        num /= 10;
    }
}

void main(void) {
    unsigned long counter = 0;  // 计数器，最大到99999999
    unsigned char digits[8];    // 存储8位数字
    unsigned int count_timer = 0;
    int pos = 0;          // 当前显示位置
    while(1) {  // 无限循环
        // 获取当前计数值的各位数字
        get_digits(counter, digits);
        // 逐位显示，实现动态扫描效果
        for(pos = 0; pos < 8; pos++) {

            bit_lock = 0; //锁住位置
            seg_lock = 1;

            P0 = seg_code[digits[pos]];
            seg_lock = 0; //锁住数字
            bit_lock = 1; //打开位置 循环pos
            // 输出位选码（选择哪个数码管）
            switch(pos) {
                case 0: P0 = 0xFE; break;  // 选通第1位 (11111110)
                case 1: P0 = 0xFD; break;  // 选通第2位 (11111101)
                case 2: P0 = 0xFB; break;  // 选通第3位 (11111011)
                case 3: P0 = 0xF7; break;  // 选通第4位 (11110111)
                case 4: P0 = 0xEF; break;  // 选通第5位 (11101111)
                case 5: P0 = 0xDF; break;  // 选通第6位 (11011111)
                case 6: P0 = 0xBF; break;  // 选通第7位 (10111111)
                case 7: P0 = 0x7F; break;  // 选通第8位 (01111111)
            }


            delay_ms(1);
            P0 = 0xFF;
            seg_lock = 0;
            bit_lock = 0;
            count_timer++;
        }


        if (count_timer>600)
        {
            count_timer = 0;
            counter++;  // 计数器递增
            if(counter > 99999999) {  // 达到最大值后重置
                counter = 0;
            }
        }
    }
}