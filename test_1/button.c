#include <STC89C5xRC.H>

// 矩阵键盘连接定义 (4x4矩阵键盘)
// 行线连接P3.0-P3.3 (作为输出)
// 列线连接P3.4-P3.7 (作为输入)
sbit ROW0 = P3^0;  // 行0
sbit ROW1 = P3^1;  // 行1
sbit ROW2 = P3^2;  // 行2
sbit ROW3 = P3^3;  // 行3
sbit COL0 = P3^4;  // 列0
sbit COL1 = P3^5;  // 列1
sbit COL2 = P3^6;  // 列2
sbit COL3 = P3^7;  // 列3
sbit sound = P2^3; //蜂鸣器
// 延时函数
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++);
}

// 矩阵键盘扫描函数（记忆优先级法）
// 返回按键值，0表示无按键，其他值表示按键编号
// 记忆第一次检测到的按键，直到所有按键释放后再重新检测
unsigned char scan_key()
{
    static unsigned char first_key_pressed = 0;  // 记忆第一个按键
    unsigned char row, col, temp_key;
    unsigned char current_scan_result = 0;

    // 设置列线为输入，行线为输出
    P3 = 0xF0;  // P3.4-P3.7设为输入(高电平)，P3.0-P3.3设为输出(低电平)

    // 检查是否有按键按下
    if((P3 & 0xF0) == 0xF0)  // 如果所有列线都是高电平，表示无按键
    {
        // 所有按键都释放了，重置记忆
        first_key_pressed = 0;
        return 0;
    }

    // 逐行扫描
    for(row = 0; row < 4; row++)
    {
        // 设置所有行线为高电平
        P3 = 0xF0;

        // 逐行拉低，扫描该行
        switch(row)
        {
            case 0: P3 = 0xFE; break;  // 11111110, 只有ROW0为低
            case 1: P3 = 0xFD; break;  // 11111101, 只有ROW1为低
            case 2: P3 = 0xFB; break;  // 11111011, 只有ROW2为低
            case 3: P3 = 0xF7; break;  // 11110111, 只有ROW3为低
        }

        // 检查哪一列被拉低
        col = P3 & 0xF0;  // 读取列线状态

        if(col != 0xF0)  // 如果有列线被拉低
        {
            switch(col)
            {
                case 0xE0:  // 11100000, COL0被拉低
                    temp_key = row * 4 + 1;  // 按键1, 5, 9, 13
                    break;
                case 0xD0:  // 11010000, COL1被拉低
                    temp_key = row * 4 + 2;  // 按键2, 6, 10, 14
                    break;
                case 0xB0:  // 10110000, COL2被拉低
                    temp_key = row * 4 + 3;  // 按键3, 7, 11, 15
                    break;
                case 0x70:  // 01110000, COL3被拉低
                    temp_key = row * 4 + 4;  // 按键4, 8, 12, 16
                    break;
                default:
                    temp_key = 0;
                    break;
            }
            
            if(temp_key != 0)
            {
                current_scan_result = temp_key;
                
                // 如果还没有记录第一个按键，则记录它
                if(first_key_pressed == 0)
                {
                    first_key_pressed = temp_key;
                }
                
                // 返回记忆的第一个按键，而不是当前扫描到的按键
                return first_key_pressed;
            }
        }
    }

    // 如果当前没有检测到按键但之前有按键被按下，返回记忆的按键
    if(first_key_pressed != 0)
    {
        return first_key_pressed;
    }

    return 0;  // 无按键按下
}

// 获取按键值（带去抖动）
unsigned char get_key()
{
    unsigned char key;

    key = scan_key();
    if(key != 0)  // 如果检测到按键
    {
        delay_ms(10);  // 延时去抖动
        if(scan_key() == key)  // 再次确认按键
            return key;
    }
    return 0;  // 无按键或抖动
}

void main()
{
    unsigned char key_value;

    // 初始化P3端口
    P3 = 0xFF;  // 设置为初始状态
    P1 = 0xFF;  // 初始化P1端口，LED全灭

    while(1)
    {
        key_value = get_key();

        if(key_value != 0)
        {
            // 这里可以处理按键事件
            // 例如：根据按键值执行不同操作

            // 简单演示：按键值显示在P1口LED上
            P1 = ~key_value;  // 显示按键值到LED（反相显示）
            sound = 0;
            // 等待按键释放
            while(get_key() != 0);
            sound = 1;
        }
        else
        {
            P1 = 0xFF;  // 无按键时LED全灭
        }
    }
}