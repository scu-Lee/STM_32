#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;
float voltage;

int main(void)
{
	/*模块初始化*/
	OLED_Init();
	AD_Init();

	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"voltage:0.00V");
	
	while (1)
	{
		ADValue=AD_GetValue();
		voltage=(float)ADValue/4095*3.3;
		
		OLED_ShowNum(1,9,ADValue,4);
		OLED_ShowNum(2,9,voltage,1);
		OLED_ShowNum(2,11,(uint16_t)(voltage*100)%100,2);
		
		Delay_ms(100);
	}
}
