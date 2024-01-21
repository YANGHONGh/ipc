#include "stm32f4xx.h"
#include "exti.h"  
#include "led.h"
#include "delay.h"
#include "bee.h"
void exti_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//使能外部中断  外部中断EXTI在APB2总线上
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//GPIO初始化
	
	GPIO_InitTypeDef GPIO_InitStructure;//结构体
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4;//选中引脚
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;//输入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//上拉模式,默认为高，连接的是VCC
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);//PD4连接到中断线
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);//PD3连接到中断线
	/*配置EXIT3线的中断*///按键一
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init( &EXTI_InitStructure);
	/*配置EXIT4线的中断*///按键二
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init( &EXTI_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn; //使能按键外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; //设置中断抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; //设置中断响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure);
	//NVIC 代表所有中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; //使能按键外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级 2，
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure);

}
//void EXTI3_IRQHandler(void) 
//{
//    if (EXTI_GetITStatus(EXTI_Line3) != RESET) 
//		{
//        PDout(14) ^=1;
//        EXTI_ClearITPendingBit(EXTI_Line3);
//    }
//}

//void EXTI3_IRQHandler(void)
//{
//   if (EXTI_GetITStatus(EXTI_Line3)!=RESET)
//   {
//		 uint32_t n = 2000 * 2;
//        while(n--)
//        {
//            Bee_ON;
//            delay_us(490);
//            Bee_OFF;
//            delay_us(10);
//        }
//				EXTI_ClearITPendingBit(EXTI_Line3);
//	 }
//	
//	
//}

void EXTI3_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line3)!= RESET)
		{
		 red_toggle();
		}
	
	EXTI_ClearITPendingBit(EXTI_Line3);

	}

void EXTI4_IRQHandler(void) 
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) 
		{
			
			int i=0;
			for(i=0;i<=400;i++)	
	{	
		  Bee_ON;
			delay_ms(1);
			Bee_OFF;
			delay_ms(1);
	}
      
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}
//void EXTI3_TRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line3)!= RESET)//判断这个线上的中断是否得到信号 line3就是按键
//	{
//	   if(GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_14) == 0)//判断灯灭
//	{
//		GPIO_SetBits (GPIOD, GPIO_Pin_14);
//	}
//	else 
//	{
//		GPIO_ResetBits (GPIOD, GPIO_Pin_14);
//	}
//}
//}	

//	EXTI_ClearITPendingBit(EXTI_Line3);
//	
//}
//}
//int t=0;
//void EXTI4_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
//	{
//		t++;
//		if(t%2==0)
//		{
//		LED3_OFF;
//		t=t+1;
//		
//		}
//		else
//		{
//		LED3_ON;
//		t=t+1;
//		}
//	
//	}	
//	EXTI_ClearITPendingBit(EXTI_Line4);
//}
