#ifndef _EXTI_H
#define _EXTI_H
 
 #include "stm32f4xx.h"
 #include "delay.h"
 void exti_init(void);
 void EXTI_3IRQHandler(void);
 void EXTI_4IRQHandler(void);
 #endif