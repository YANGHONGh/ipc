#include "stm32f4xx.h"
#include "exti.h"  
#include "led.h"
#include "delay.h"
#include "bee.h"
void exti_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//ʹ���ⲿ�ж�  �ⲿ�ж�EXTI��APB2������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//GPIO��ʼ��
	
	GPIO_InitTypeDef GPIO_InitStructure;//�ṹ��
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4;//ѡ������
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;//����ģʽ
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//����ģʽ,Ĭ��Ϊ�ߣ����ӵ���VCC
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);//PD4���ӵ��ж���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);//PD3���ӵ��ж���
	/*����EXIT3�ߵ��ж�*///����һ
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init( &EXTI_InitStructure);
	/*����EXIT4�ߵ��ж�*///������
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init( &EXTI_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn; //ʹ�ܰ����ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; //�����ж���ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; //�����ж���Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure);
	//NVIC ���������ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; //ʹ�ܰ����ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ� 2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ� 2
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
//	if(EXTI_GetITStatus(EXTI_Line3)!= RESET)//�ж�������ϵ��ж��Ƿ�õ��ź� line3���ǰ���
//	{
//	   if(GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_14) == 0)//�жϵ���
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
