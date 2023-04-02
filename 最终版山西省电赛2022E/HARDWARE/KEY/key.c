#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
int b=0;
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0 KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成浮空输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0,1

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;  //KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //浮空
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOB.12

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;  //KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //浮空
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOB.12
	
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)
			{
				b=b+1;
				if(b>1)
					b=0;
			return KEY0_PRES;
		  }
		else if(KEY1==0)
			{
				b=b+2;
				if(b>2)
					b=0;
			return KEY1_PRES;
		  }
		else if(KEY2==0)
			{
				b=b+3;
				if(b>3)
					b=0;
			return KEY2_PRES;
		  }
		else if(KEY3==0)
			{
				b=b+4;
				if(b>4)
					b=0;
			return KEY3_PRES;
		  }
		else if(KEY4==0)
			{
				b=b+5;
				if(b>5)
					b=0;
			return KEY4_PRES;
		  }
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	    
 	return 0;// 无按键按下
}
