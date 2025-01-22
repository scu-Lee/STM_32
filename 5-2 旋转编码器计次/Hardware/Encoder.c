#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;//全局变量，用于计数

void Encoder_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO的时钟，外部中断必须开启AFIO的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	/*AFIO选择中断引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStructure;//定义结构体变量
	EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);//将结构体变量交给EXTI_Init，配置EXTI外设
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置NVIC为分组2
	//即抢占优先级范围：0~3，响应优先级范围：0~3
	//此分组配置在整个工程中仅需调用一次
	//若有多个中断，可以把此代码放在main函数内，while循环之前
	//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	NVIC_InitTypeDef NVIC_InitStructure;//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);//将结构体变量交给NVIC_Init，配置NVIC外设
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);//将结构体变量交给NVIC_Init，配置NVIC外设
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp=Encoder_Count;
	Encoder_Count=0;
	return Temp;
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
				Encoder_Count--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			Encoder_Count++;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}