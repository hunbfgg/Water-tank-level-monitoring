#include "SIMxxx.h"
#include "lcd.h"
#include "delay.h"

u8 SIM900_CSQ[4];
u8* sim900a_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART1_RX_STA&0X8000)		//
	{ 
		USART1_RX_BUF[USART1_RX_STA&0X7FFF]=0;//
		strx=strstr((const char*)USART1_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{	
	u8 res=0;
	USART1_RX_STA=0;USART1_RX_REC_ATCOMMAD=1;
	UART1_SendString(cmd);
	if(ack&&waittime)		
	{
		while(--waittime)	
		{
			delay_ms(10);
			if(USART1_RX_STA&0X8000)
			{
				if(sim900a_check_cmd(ack))break; 
				USART1_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	USART1_RX_STA=0;USART1_RX_REC_ATCOMMAD=0;
	return res;
}
u8 sim900a_work_test(void)
{
	if(sim900a_send_cmd((u8 *)"AT\r\n",(u8 *)"OK",100))
	{
		if(sim900a_send_cmd((u8 *)"AT\r\n",(u8 *)"OK",100))return SIM_COMMUNTION_ERR;	//通信不上
	}		
	if(sim900a_send_cmd((u8 *)"AT+CPIN?\r\n",(u8 *)"READY",400))return SIM_CPIN_ERR;	//没有SIM卡
	if(sim900a_send_cmd((u8 *)"AT+CREG?\r\n",(u8 *)"0,1",400))
	{
		if(strstr((const char*)USART1_RX_BUF,"0,5")==NULL)
		{
			 if(!sim900a_send_cmd((u8 *)"AT+CSQ\r\n",(u8 *)"OK",200))	
			 {
				memcpy(SIM900_CSQ,USART1_RX_BUF+15,2);
			 }
			 return SIM_CREG_FAIL;	//等待附着到网络
		}
	}
	return SIM_OK;
}
u8 SIM900A_CONNECT_SERVER()
{		
//	u8 	 dtbuf[50];
	if(sim900a_send_cmd((u8 *)"AT+CGCLASS=\"B\"\r\n",(u8 *)"OK",500))	return 1;
	xianshi_x_y(1,5,"1",1);
	if(sim900a_send_cmd((u8 *)"AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n",(u8 *)"OK",500))	return 7;
	xianshi_x_y(1,5,"2",1);
	if(sim900a_send_cmd((u8 *)"AT+CGATT=1\r\n",(u8 *)"OK",500))	return 2;
	xianshi_x_y(1,5,"3",1);
//	if(sim900a_send_cmd((u8 *)"AT+CSTT\r\n",(u8 *)"OK",200))	return 3;
//	xianshi_x_y(1,5,"4",1);
//	if(sim900a_send_cmd((u8 *)"AT+CIICR\r\n",(u8 *)"OK",600))	return 4;
//	if(!sim900a_send_cmd((u8 *)"AT+CIFSR\r\n",(u8 *)"ERROR",200))	return 5;
//	if(sim900a_send_cmd((u8 *)"AT+CIPCSGP=1,\"CMNET\"\r\n",(u8 *)"OK",200))	return 4;
//	xianshi_x_y(1,5,"5",1);
	if(sim900a_send_cmd((u8 *)"AT+CLPORT=\"TCP\",\"2000\"\r\n",(u8 *)"OK",200))	return 3;
	xianshi_x_y(1,5,"6",1);
//	sprintf((char*)dtbuf,"AT+CIPSTART=\"TCP\",\"%s\",\"%s\"\r\n",IP_ADD,COM);
	delay_ms(500);
//	if(sim900a_send_cmd((u8 *)dtbuf,(u8 *)"CONNECT OK",200))	return 6;		
//	if(sim900a_send_cmd((u8 *)dtbuf,(u8 *)"OK",200))	return 6;	
		if(sim900a_send_cmd((u8 *)"AT+CIPSTART=\"TCP\",\"www.bigiot.net\",\"8181\"\r\n",(u8 *)"CONNECT OK",200))	return 6;	
		xianshi_x_y(1,5,"7",1);
	  return 0;
}
u8 SIM900A_GPRS_SEND_DATA()
{		
	 u8 cmd_1[3];
	 //UART3SendString("启动数据发送，数据内容：",strlen("启动数据发送，数据内容："));	
	 if(sim900a_send_cmd("AT+CIPSEND\r\n",">",200))	 return 1;
			xianshi_x_y(1,5,"8",1);
	 //UART3SendString((u8*)temp_data,strlen((u8*)temp_data));	UART3SendString("\r\n",2);
	 if(sim900a_send_cmd((u8 *)"{\"M\":\"checkin\",\"ID\":\"19978\",\"K\":\"d8bb4cca4\"}\r\n",NULL,50))	return 2;
			
	 cmd_1[0]=0x1a;cmd_1[1]=0;
	xianshi_x_y(1,5,"9",1);
	 if(sim900a_send_cmd(cmd_1,(u8 *)"SEND OK",3000))	return 3;		
//	UART1_SendString(0x1A);
		xianshi_x_y(1,5,"0",1);
	 //UART3SendString("数据发送成功",strlen("数据发送成功"));	UART3SendString("\r\n",2);
	 return 0;
}

