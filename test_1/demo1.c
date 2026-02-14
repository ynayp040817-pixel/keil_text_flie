#include <STC89C5xRC.H>

// 定义LED连接的端口（假设连接到P2口）
#define LED_PORT P1

// 延时函数 - 更精确的延时
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++); // 根据12MHz晶振调整延时系数
}

// 主函数
void main()
{
    // 初始化LED端口
    LED_PORT = 0xFF;  // 先将P2口全部设为高电平（LED熄灭，如果是共阳极连接）
    
    while(1)
    {
        // LED亮（根据实际电路连接，可能是低电平点亮）
        LED_PORT = 0x00;  // P2口全部输出低电平
        delay_ms(500);    // 延时500ms
        
        // LED灭
        LED_PORT = 0xFF;  // P2口全部输出高电平
        delay_ms(500);    // 延时500ms
    }
}