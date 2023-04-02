#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"
#include "stdio.h"
extern uint8_t brr[20];
extern uint8_t arr[10];
extern uint8_t Rxover;
void USART1_Receive(void);
void USART1_Init(int Baud);
//void USART2_Init(void);
void USART1_SendString(uint8_t *str);
//void USART2_SendString(uint8_t *str);

#endif
