#ifndef __DISPLAY__
#define __DISPLAY__
#include "stm32f10x.h"
#include "mlx90614.h"

extern float dis;
extern	sMlx90614Typ sMlx;
extern u8 matched;
extern u8 state;
extern u8 change;
extern float temp;
extern u8  mode;
extern uint8_t Rxover;
extern uint8_t brr[20];
//extern unsigned char Temp[6];
void Learn_dispaly(void);
void Learn_extract(void);
void Dispaly(void);
void Tem_Dispaly(void); //使用前初始化LCD 温度显示
void Obj_Dispaly(void);
void Face_Dispaly(void);
void Face_Rec(void);
void Mask_dispaly(void);
void Mask_Rec(void);   
#endif
