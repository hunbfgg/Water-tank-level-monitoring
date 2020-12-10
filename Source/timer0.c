#include "TIMER0.h"
sbit RUNING_LED=P2^1;

void Timer0Init(void)		//10����@115200
{
	AUXR &= 0x7F;		
	TMOD &= 0xF0;		
	TMOD |= 0x01;		//
	TL0 = 0x00;		//
	TH0 = 0xDC;		//
	TF0 = 0;		//
	ET0 = 1;    	  //
	TR0 = 0;		//ֹͣ��ʱ
}
void TIM_SetCounter(void)			  //����װֵ
{
	TL0 = 0x00;		//
	TH0 = 0xDC;		//
}
/*******************************************************************************
* ������ : Timer0_ISR
* ����   : ��ʱ��0�жϷ�����ں���,20ms�ж�һ��
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Timer0_ISR() interrupt 1
{
	TR0=0;//�ض�ʱ��
	USART1_RX_STA|=1<<15;	//
	USART1_RX_BUF[USART1_RX_STA&0X7FFF]=0;//��ӽ�����
	if(!USART1_RX_REC_ATCOMMAD)	
	{		
		USART1_RX_STA=0;		
		if(strstr((char*)USART1_RX_BUF,"RING")!=NULL)	Flag_Rec_Call=1;//����Ƿ������绰��
	}	
}