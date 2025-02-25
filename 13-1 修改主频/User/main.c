#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	
	OLED_ShowString(1,1,"SYSCLK:");
	OLED_ShowNum(1,8,SystemCoreClock,8);//		系统文件system_stm32f10x.c修改主频
	
	while (1)
	{
		OLED_ShowString(2,1,"Runing");
		Delay_ms(500);
		OLED_ShowString(2,1,"      ");
		Delay_ms(500);
	}
}
