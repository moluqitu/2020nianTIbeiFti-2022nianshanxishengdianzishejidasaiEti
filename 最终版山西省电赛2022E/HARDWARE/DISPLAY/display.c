#include "display.h"
#include "oled.h"
#include "beef.h"
#include "mlx90614.h"
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

extern float a;
float temp=0;
unsigned char Temp[6];

char name1[]="JiChenChen";
char name2[]="LiuYiFan";
char name3[]="LuoZhiTai";
char name4[]="Stanger1";
char name5[]="Stanger2";
char name6[]="Stanger3";
char *name[6]={name1,name2,name3,name4,name5,name6};
uint8_t face_max[10];
uint8_t name_num=0;
uint8_t Mask_pixels[10];//当前像素点+阈值
uint8_t flag_Mask=0;//口罩识别位
uint8_t *Threshold[3]={"blue","l_blue","black"};//色域选择
uint8_t Threshold_num;



void Tem_Dispaly() 
{
		float	fTbody;
//		change = 1;
			/* 获取环境温度 */
		ucMLX90614_GetTA(&sMlx) ;
		/* 获取人体额头温度 */
		ucMLX90614_GetTO1(&sMlx) ;
		/* 计算补偿后的人体温度 */
		fTbody = ucMLX90614_TempComp(&sMlx) ;
		if(sMlx.Ta>37.5)
		{
			fTbody=37.5;
		}
		OLED_ShowCHinese(0,0,18);
		OLED_ShowCHinese(16,0,19);
		OLED_ShowString(32,0,":  .  C",16);
		OLED_ShowNum(40,0,(int)(sMlx.Ta)%100,2,16);
		OLED_ShowNum(64,0,(int)(sMlx.Ta*100)%100,2,16);
		OLED_ShowCHinese(0,2,6);
		OLED_ShowCHinese(16,2,0);
		OLED_ShowString(32,2,":  .  C",16);
		OLED_ShowNum(40,2,(int)(fTbody)%100,2,16);
		OLED_ShowNum(64,2,(int)(fTbody*100)%100,2,16);
		OLED_ShowCHinese(0,4,20);
		OLED_ShowCHinese(16,4,21);
		OLED_ShowCHinese(32,4,22);
		OLED_ShowCHinese(48,4,23);
		OLED_ShowString(64,4,":  . C",16);
		OLED_ShowNum(72,4,(int)(a)%100,2,16);
		OLED_ShowNum(96,4,(int)(a*10)%10,1,16);
		if(fTbody>a)
		{
      LED0=0;
			BEEF=0;
			OLED_ShowCHinese(0,6,26);
			OLED_ShowCHinese(16,6,24);
			OLED_ShowCHinese(32,6,25);
		}
		if(fTbody<=a)
		{
      LED0=1;
			BEEF=1;
			OLED_ShowCHinese(0,6,24);
			OLED_ShowCHinese(16,6,25);
			OLED_ShowString(32,6,"  ",16);
		}
}

void Obj_Dispaly() 
{
		float	fTbody;
//		change = 1;
			/* 获取环境温度 */
		ucMLX90614_GetTA(&sMlx) ;
		/* 获取人体额头温度 */
		ucMLX90614_GetTO1(&sMlx) ;
		/* 计算补偿后的人体温度 */
		fTbody = ucMLX90614_TempComp(&sMlx) ;
		if(sMlx.Ta>37.5)
		{
			fTbody=37.5;
		}
		OLED_ShowCHinese(0,0,18);
		OLED_ShowCHinese(16,0,19);
		OLED_ShowString(32,0,":  .  C",16);
		OLED_ShowNum(40,0,(int)(sMlx.Ta)%100,2,16);
		OLED_ShowNum(64,0,(int)(sMlx.Ta*100)%100,2,16);
		OLED_ShowCHinese(0,2,7);
		OLED_ShowCHinese(16,2,0);
		OLED_ShowString(32,2,":  .  C",16);
		OLED_ShowNum(40,2,(int)(sMlx.To1)%100,2,16);
		OLED_ShowNum(64,2,(int)(sMlx.To1*100)%100,2,16);
		OLED_ShowCHinese(0,4,20);
		OLED_ShowCHinese(16,4,21);
		OLED_ShowCHinese(32,4,22);
		OLED_ShowCHinese(48,4,23);
		OLED_ShowString(64,4,":  . C",16);
		OLED_ShowNum(72,4,(int)(a)%100,2,16);
		OLED_ShowNum(96,4,(int)(a*10)%10,1,16);
		if(sMlx.To1>a)
		{
      LED0=0;
			BEEF=0;
			OLED_ShowCHinese(0,6,26);
			OLED_ShowCHinese(16,6,24);
			OLED_ShowCHinese(32,6,25);
		}
		if(sMlx.To1<=a)
		{
      LED0=1;
			BEEF=1;
			OLED_ShowCHinese(0,6,24);
			OLED_ShowCHinese(16,6,25);
			OLED_ShowString(32,6,"  ",16);
		}
}

void	Face_Dispaly()
{
	OLED_ShowCHinese(32,0,12);
	OLED_ShowCHinese(48,0,13);
	OLED_ShowCHinese(64,0,14);
	OLED_ShowCHinese(80,0,15);
	
	OLED_ShowCHinese(0,2,14);
	OLED_ShowCHinese(16,2,15);
	OLED_ShowCHinese(32,2,34);
	OLED_ShowCHinese(48,2,35);
	OLED_ShowString(64,2,":",16);
	
	OLED_ShowCHinese(0,4,30);
	OLED_ShowCHinese(16,4,31);
	OLED_ShowString(32,4,":",16);
	
	OLED_ShowCHinese(0,6,32);
	OLED_ShowCHinese(16,6,33);
	OLED_ShowString(32,6,":",16);
}
void Face_Rec(void)
{
	 if(Rxover==1)
  {
	  uint8_t i;
		i=brr[0];
		switch(i)
		{
			case '0':matched=2;OLED_ShowCHinese(40,4,46);OLED_ShowCHinese(56,4,47);OLED_ShowCHinese(72,4,12);OLED_ShowString(88,4,"      ",16);break;
			case '3':matched=1;OLED_ShowCHinese(40,4,37);OLED_ShowCHinese(56,4,38);OLED_ShowCHinese(72,4,39);OLED_ShowString(88,4,"      ",16);break;
			case '4':matched=1;OLED_ShowCHinese(40,4,40);OLED_ShowCHinese(56,4,41);OLED_ShowCHinese(72,4,42);OLED_ShowString(88,4,"      ",16);break;
			case '5':matched=1;OLED_ShowCHinese(40,4,43);OLED_ShowCHinese(56,4,44);OLED_ShowCHinese(72,4,45);OLED_ShowString(88,4,"      ",16);break;
			case '7':matched=1;OLED_ShowCHinese(40,4,16);OLED_ShowCHinese(56,4,17);OLED_ShowCHinese(72,4,34);OLED_ShowCHinese(88,4,35);OLED_ShowString(104,4,"1   ",16);break;
			case '8':matched=1;OLED_ShowCHinese(40,4,16);OLED_ShowCHinese(56,4,17);OLED_ShowCHinese(72,4,34);OLED_ShowCHinese(88,4,35);OLED_ShowString(104,4,"2   ",16);break;
			case '9':matched=1;OLED_ShowCHinese(40,4,16);OLED_ShowCHinese(56,4,17);OLED_ShowCHinese(72,4,34);OLED_ShowCHinese(88,4,35);OLED_ShowString(104,4,"3   ",16);break;
			
		}
		if(matched==1)
		{
			BEEF=1;
			LED0=1;
	    OLED_ShowCHinese(72,2,28);//成
	    OLED_ShowCHinese(88,2,29);//功
			OLED_ShowString(104,2,"   ",16);
			
			OLED_ShowCHinese(48,6,24);//正常
			OLED_ShowCHinese(64,6,25);
			OLED_ShowString(80,6,"  ",16);
		}
		else if(matched==2)
		{
			BEEF=0;
      LED0=0; 
			OLED_ShowCHinese(72,2,26);//不成功
	    OLED_ShowCHinese(88,2,28);
			OLED_ShowCHinese(104,2,29);
			
			OLED_ShowCHinese(48,6,26);//不正常
			OLED_ShowCHinese(64,6,24);
			OLED_ShowCHinese(80,6,25);	
		}
		Rxover=0;
	}
}
void Learn_dispaly(void)
{
	OLED_ShowCHinese(32,0,12);
	OLED_ShowCHinese(48,0,13);
	OLED_ShowCHinese(64,0,16);
	OLED_ShowCHinese(80,0,17);
	
	OLED_ShowCHinese(0,4,16);
	OLED_ShowCHinese(16,4,17);
	OLED_ShowCHinese(32,4,34);
	OLED_ShowCHinese(48,4,35);
	OLED_ShowString(64,4,":",16);
}
void Learn_extract(void)
{
	if(Rxover==1)
 {
	uint8_t i;
	i=brr[0];
	if(i=='6')
	{
		OLED_ShowCHinese(72,4,28);//成
	  OLED_ShowCHinese(88,4,29);//功
	  OLED_ShowString(104,4,"   ",16);
	}
	if(i=='A')
	{
		OLED_ShowCHinese(72,4,53);//库已满
	  OLED_ShowCHinese(88,4,54);
	  OLED_ShowCHinese(104,4,55);
	}
   Rxover=0;
 }
}
void Mask_dispaly(void)
{
	OLED_ShowCHinese(32,0,8);
	OLED_ShowCHinese(48,0,9);
	OLED_ShowCHinese(64,0,10);
	OLED_ShowCHinese(80,0,11);
	
	OLED_ShowCHinese(0,2,10);
	OLED_ShowCHinese(16,2,11);
	OLED_ShowCHinese(32,2,34);
	OLED_ShowCHinese(48,2,35);
	OLED_ShowString(64,2,":",16);
}	
void Mask_Rec(void) 
{
 if(Rxover==1)
 {
	uint8_t i;
	i=brr[0];
	if(i=='1')
	{
		OLED_ShowCHinese(72,2,28);//成
	  OLED_ShowCHinese(88,2,29);//功
	  OLED_ShowString(104,2,"   ",16);
		
		OLED_ShowCHinese(0,4,48);
  	OLED_ShowCHinese(16,4,49);
  	OLED_ShowCHinese(32,4,50);
  	OLED_ShowCHinese(48,4,51);
		OLED_ShowCHinese(64,4,52);
		OLED_ShowString(80,4,"     ",16);
	}
	if(i=='2')
	{
		OLED_ShowCHinese(72,2,26);//不成功
	  OLED_ShowCHinese(88,2,28);
	  OLED_ShowCHinese(104,2,29);
		
		OLED_ShowCHinese(0,4,48);
	  OLED_ShowCHinese(16,4,49);
	  OLED_ShowCHinese(32,4,26);
	  OLED_ShowCHinese(48,4,50);
		OLED_ShowCHinese(64,4,51);
		OLED_ShowCHinese(80,4,52);
	}
	Rxover=0;
 }
}


