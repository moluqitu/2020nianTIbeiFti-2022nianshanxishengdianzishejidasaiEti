#include "exit1.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "mlx90614.h"
#include "stm32f10x.h"
#include "beef.h"


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
float a=35.0;
static int c=0;

void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI3_IRQHandler(void)
{
	
	delay_ms(10);
	if(KEY5==0)
	{
		if(a<46)
		a=a+0.5;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
	  
}

void EXTI4_IRQHandler(void)
{
	
	delay_ms(10);
	if(KEY6==0)
	{
		if(a>30)
		a=a-0.5;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
	  
}

void EXTI0_IRQHandler(void)
{
	
	delay_ms(10);
	if(KEY2==0)
	{
		USART_SendData(USART1,'1');
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
	  
}

void EXTI2_IRQHandler(void)
{
	
	delay_ms(10);
	if(KEY4==0)
	{
		  USART_SendData(USART1,'B');
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
	  
}

void EXTI15_10_IRQHandler(void)
{
	
	delay_ms(10);
	if(KEY3==0)
	{
		if(c%2==0)
	 {
		USART_SendData(USART1,'2');
	 }
	 c++;
	}
	EXTI_ClearITPendingBit(EXTI_Line14);
	  
}

 
