#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int16_t Num;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	
	Encoder_Init();
	
	/*OLED显示*/
	OLED_ShowString(1, 1, "Num");				//1行1列显示Num
	
	while (1)
	{
		Num += Encoder_Get();
		OLED_ShowSignedNum(1,7,Num,5);
	}
}
