#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "mlx90614.h"
#include "oled.h"
#include "exit1.h"
#include "beef.h"
#include "usart1.h"
#include "smbus.h"
#include "display.h"
 
/************************************************
 ALIENTEK精英STM32开发板实验4
 串口 实验   
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

uint8_t brr[20];
uint8_t arr[10];
uint8_t Rxover=0;
extern int b;
//unsigned char Temp[10];

sMlx90614Typ sMlx;
u8  mode=0;
u8 matched,state,change;
u8 stranger=1;
float dis;

extern void usart2_init(u32 bound);
extern void vSMBus_Init(void);
 int main(void)
 {		
	extern float a;            //阈值
	u8 ls_mode=0;//当前模式
	vu8 key=0;
	delay_init();	    	 //延时函数初始化	
  SysTick_CLKSourceConfig(1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	USART1_Init(115200);
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	vSMBus_Init();        //GY906初始化
	OLED_Init();          //oled初始化
  OLED_Clear();
	EXTIX_Init();
	BEEP_Init();	
	vMLX90614_Init(&sMlx,MLX90614_SMBUS_ADDR);
 	while(1)
	{
		mode = KEY_Scan(0);
    if(b==1)
      mode=1;	
    if(b==2)
      mode=2;
    if(b==3)
      mode=3;
    if(b==4)
      mode=4;
    if(b==5)
      mode=5;
		if(ls_mode != mode)
		{
			OLED_Clear(); //模式变化时清屏
			LED0=1;
			BEEF=1;
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			ls_mode = mode;
		}
		
		switch(ls_mode)
		{
			case 0:	OLED_ShowCHinese(0,0,4);OLED_ShowCHinese(16,0,5);OLED_ShowString(32,0,"1:",16);OLED_ShowCHinese(48,0,6);OLED_ShowCHinese(64,0,0);OLED_ShowString(80,0,"2:",16);OLED_ShowCHinese(96,0,7);OLED_ShowCHinese(112,0,0);
		          OLED_ShowCHinese(0,2,4);OLED_ShowCHinese(16,2,5);OLED_ShowString(32,2,"3:",16);OLED_ShowCHinese(48,2,12);OLED_ShowCHinese(64,2,13);OLED_ShowCHinese(80,2,14);OLED_ShowCHinese(96,2,15);
		          OLED_ShowCHinese(0,4,4);OLED_ShowCHinese(16,4,5);OLED_ShowString(32,4,"4:",16);OLED_ShowCHinese(48,4,12);OLED_ShowCHinese(64,4,13);OLED_ShowCHinese(80,4,16);OLED_ShowCHinese(96,4,17);
		          OLED_ShowCHinese(0,6,4);OLED_ShowCHinese(16,6,5);OLED_ShowString(32,6,"5:",16);OLED_ShowCHinese(48,6,8);OLED_ShowCHinese(64,6,9);OLED_ShowCHinese(80,6,10);OLED_ShowCHinese(96,6,11);
		          delay_ms(100);Hy=0;
							break;         //主界面
			
			case 1: Tem_Dispaly();            //人体温度
			        Hy=1;
							break;
			
			case 2:	Obj_Dispaly();								//物体温度 
						  Hy=1;
							break;
			
			case 3: Face_Dispaly();
				      Face_Rec();								//队内识别
			        Hy=0;
							break;						
			
			case 4:	Learn_dispaly();          //队友配对
							Learn_extract();
							Hy=0;
							break;	
							
      case 5:	Mask_dispaly();			//陌生人信息录入
							Mask_Rec();
							Hy=0;
							break;							
		}
	} 
 }

