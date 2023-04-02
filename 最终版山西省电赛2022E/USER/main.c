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
 ALIENTEK��ӢSTM32������ʵ��4
 ���� ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
	extern float a;            //��ֵ
	u8 ls_mode=0;//��ǰģʽ
	vu8 key=0;
	delay_init();	    	 //��ʱ������ʼ��	
  SysTick_CLKSourceConfig(1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	vSMBus_Init();        //GY906��ʼ��
	OLED_Init();          //oled��ʼ��
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
			OLED_Clear(); //ģʽ�仯ʱ����
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
							break;         //������
			
			case 1: Tem_Dispaly();            //�����¶�
			        Hy=1;
							break;
			
			case 2:	Obj_Dispaly();								//�����¶� 
						  Hy=1;
							break;
			
			case 3: Face_Dispaly();
				      Face_Rec();								//����ʶ��
			        Hy=0;
							break;						
			
			case 4:	Learn_dispaly();          //�������
							Learn_extract();
							Hy=0;
							break;	
							
      case 5:	Mask_dispaly();			//İ������Ϣ¼��
							Mask_Rec();
							Hy=0;
							break;							
		}
	} 
 }

