/**********************************************************************************
 //SIMXXX系列开发板底层代码
 //全球鹰电子@UNV
 //版本号;V1.0
 //官方淘宝店地址：https://shop110330041.taobao.com
 //版权所有，盗版必究
 * 工程名  :通TCP方式，向服务器提交数据
 * 描述    :向固定的服务器地址，上传测试数据
 * 实验平台:STC89XX
 * 库版本  :

**********************************************************************************/

#include "string.h"
#include "delay.h"
#include "uart.h"
#include "timer0.h"
#include "SIMxxx.h"
#include "lcd.h"


/*************  外部函数和变量声明*****************/
/*******************************************************************************
* 函数名 : main 
* 描述   : 主函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void main(void)
{
	u8 flag=1;
	u8 cmd_1[3];
	u8 res;
	Uart1Init();
	LcdInit();
	Timer0Init();
	EA=1;	//开总中断
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
		res=SIM900A_CONNECT_SERVER();   //实际应用时，只需要更改此处的服务器地址即可
	}
	xianshi_x_y(2,5,"2_OK",4);
	res=1;
	while(res)
	{
		res=SIM900A_GPRS_SEND_DATA();		   //可更改为自己想要发送的内容																							//UNCION编码工具一般在资料包工具文件夹内
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




