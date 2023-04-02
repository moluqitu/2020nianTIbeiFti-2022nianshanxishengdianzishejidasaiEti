#include "usart1.h"
#include "stm32f10x.h"
void USART1_Init(int Baud)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);


		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	


		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_Init(&NVIC_InitStructure);

		USART_InitStructure.USART_BaudRate = Baud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}


//void USART2_Init(void)
//{
//		GPIO_InitTypeDef GPIO_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
//		USART_InitTypeDef USART_InitStructure;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);


//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);

//		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//		NVIC_Init(&NVIC_InitStructure);

//		USART_InitStructure.USART_BaudRate = 9600;
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;
//		USART_InitStructure.USART_Parity = USART_Parity_No;
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//		USART_Init(USART2, &USART_InitStructure);
//		USART_Cmd(USART2, ENABLE);
//		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//}
int fputc(int ch,FILE *f)
{
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_SendData(USART1,(uint8_t) ch);

	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);
	return (ch);
}
void USART1_SendString(uint8_t *str)
{
	while(*str)
	{
		USART_SendData(USART1,*str++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==0);
	}
}


void USART1_Receive(void)//uint8_t *str
{
	
//		if (Rxover==1)
//		{
////						USART1_SendString(arr);
//						Rxover=0;
//		}
}


