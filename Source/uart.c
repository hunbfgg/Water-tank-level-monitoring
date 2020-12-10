#include "uart.h"
#include "timer0.h"

u16 USART1_RX_STA=0;  
u8 USART1_RX_REC_ATCOMMAD;
u8 Flag_Rec_Call=0;
xdata u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 				//

void Uart1Init(void)		//9600bps@11.05926MHz
{
	PCON &= 0x7F;		//
	SCON = 0x50;		//
	AUXR &= 0xBF;		//
	AUXR &= 0xFE;		//
	TMOD &= 0x0F;		//
	TMOD |= 0x20;		//
	TL1 = 0xFD;		  //
	TH1 = 0xFD;		  //
	ET1 = 0;		    //
	TR1 = 1;		    //
  ES=1;					//
}
/*----------------------------
UART1 ���ʹ�������
-----------------------------*/
void UART1_SendData(u8 dat)
{
	ES=0;					//�ش����ж�
	SBUF=dat;			
	while(TI!=1);	//�ȴ����ͳɹ�
	TI=0;					//��������жϱ�־
	ES=1;					//�������ж�
}
/*----------------------------
UART1 �����ַ���
-----------------------------*/
void UART1_SendString(char *s)
{
	while(*s)//����ַ���������
	{
		UART1_SendData(*s++);//���͵�ǰ�ַ�
	}
}
///*----------------------------
//UART1 �����ַ���
//������� ������ظ�����
//-----------------------------*/
//void UART1_SendString_other(char *s)
//{
//	while(*s)//����ַ���������
//	{
//		UART1_SendData(*s++);//���͵�ǰ�ַ�
//	}
//}
/*******************************************************************************
* ������ : Uart1 
* ����   : ����1�жϷ�����ں���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
******************************/
void Uart1_INTER() interrupt 4
{
	if (RI)
    {
      RI = 0;                 //���RIλ  
	  if(USART1_RX_STA<USART1_MAX_RECV_LEN)		//?1?����??����?��y?Y
	  {	  	
		TIM_SetCounter();
		if(USART1_RX_STA==0)	TR0=1;	 	//������ʱ��
		USART1_RX_BUF[USART1_RX_STA++]=SBUF;		//���洮������
	  }
	  else 
	  {
		USART1_RX_STA|=1<<15;					//????����???����?����3��
  	  } 
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
    }
}


