/**********************************************************************************
 //SIMXXXϵ�п�����ײ����
 //ȫ��ӥ����@UNV
 //�汾��;V1.0
 //�ٷ��Ա����ַ��https://shop110330041.taobao.com
 //��Ȩ���У�����ؾ�
 * ������  :ͨTCP��ʽ����������ύ����
 * ����    :��̶��ķ�������ַ���ϴ���������
 * ʵ��ƽ̨:STC89XX
 * ��汾  :

**********************************************************************************/

#include "string.h"
#include "delay.h"
#include "uart.h"
#include "timer0.h"
#include "SIMxxx.h"
#include "lcd.h"


/*************  �ⲿ�����ͱ�������*****************/
/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void main(void)
{
	u8 flag=1;
	u8 cmd_1[3];
	u8 res;
	Uart1Init();
	LcdInit();
	Timer0Init();
	EA=1;	//�����ж�
	res=1;
	xianshi_x_y(2,5,"work",4);	
	while(res)
	{
		res=sim900a_work_test();
	}
	xianshi_x_y(2,5,"1_OK",4);
	res=1;
	while(res)
	{
		res=SIM900A_CONNECT_SERVER();   //ʵ��Ӧ��ʱ��ֻ��Ҫ���Ĵ˴��ķ�������ַ����
	}
	xianshi_x_y(2,5,"2_OK",4);
	res=1;
	while(res)
	{
		res=SIM900A_GPRS_SEND_DATA();		   //�ɸ���Ϊ�Լ���Ҫ���͵�����																							//UNCION���빤��һ�������ϰ������ļ�����
	}
		while(1)
	{
		
		xianshi_x_y(2,5,"3_OK",4);	
	if(flag)
	{
	 if(sim900a_send_cmd("AT+CIPSEND\r\n",">",200))	 flag=1;
		
	 if(sim900a_send_cmd((u8 *)"{\"M\":\"update\",\"ID\":\"19978\",\"V\":{\"17935\":\"1\"}}\r\n",NULL,50))	flag=1;
	 cmd_1[0]=0x1a;cmd_1[1]=0;
	 
	 if(sim900a_send_cmd(cmd_1,(u8 *)"SEND OK",3000))	flag=1;		
	
		flag=0;
	 
	}
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
	flag=1;
	}
}




