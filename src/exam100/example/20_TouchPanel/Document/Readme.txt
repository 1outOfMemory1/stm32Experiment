/***********************************************************************************
 TouchPanel 驱动  huo  2016-08-26  09:00
 IIC IO：IIC_SCL-PB6  IIC_SDA-PB7
 TouchPanel_ADDR  0x80
 Timer6用于触摸屏定时扫描
 Delay 用于延时
 USART1 IO：TX1-PA9 RX1-PA10 支持printf
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
MK64_STM32三核心教学科研平台
STM32F103ZET6核心板
核心板上S2拨码拨至0端。

21_TouchPanel
电容触摸屏驱动实验，串口 COM1 输出“load firmware success.!”，支持定时扫描和中断两种。
