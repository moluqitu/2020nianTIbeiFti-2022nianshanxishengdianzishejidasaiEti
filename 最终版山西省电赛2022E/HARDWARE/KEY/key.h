#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ����1
#define KEY2   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����2
#define KEY3   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//��ȡ����3
#define KEY4   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//��ȡ����2
#define KEY5   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ����3
#define KEY6   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����3


 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define KEY2_PRES   3	//KEY2����
#define KEY3_PRES   4	//KEY3����
#define KEY4_PRES   5	//KEY2����
#define KEY5_PRES   6	//KEY3����
#define KEY6_PRES   7	//KEY3����


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
