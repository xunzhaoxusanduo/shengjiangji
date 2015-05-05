#include"SST89x5x4.h"
#include "main.h"
#include "key.h"
#include "X5045.h"
#include "init.h"
#include "motor.h"
sfr16 Timer0 = 0x8C;
unsigned int uiSet_Value = B_VALUE;
bit bFisrt_Init = FALSE;


/***
  * ���ܣ�
        ��ʱ��0��ʼ��
  * ������
        ��
  * ���أ�
        ��
  * ��ע��
***/
void Timer0_init(void)
{	
	TMOD = 0x01;             	//T0��ʱ�������ڷ�ʽ1

	Timer0 = RELOAD_VALUE;		//10ms���
	TF0 = 0;                 
    TR0 = 1;                 	//start up the timer0
}


/***
  * ���ܣ�
        ���ڳ�ʼ��
  * ������
        ��
  * ���أ�
        ��
  * ��ע��
***/
void uart_init(void)
{	
	TMOD |= 0x20;             	//T1��ʱ�������ڷ�ʽ1
	TH1 = 0xfd;					//9600
	TL1 = 0xfd;
	SCON = 0x50;
	PCON &= 0x7f;
	TR1 = 1;
}


/***
  * ���ܣ�
        I/O�ڳ�ʼ��
  * ������
        ��
  * ���أ�
        ��
  * ��ע��
***/
void port_init(void)
{	
	
}


/***
  * ���ܣ�
        �ж�ʹ��
  * ������
        ��
  * ���أ�
        ��
  * ��ע��
***/
void interrupt_init(void)
{	
	ET0 = 1;   //enable timer0 interrupt
	ES = 1;    //enable uart interrupt
	EA = 1;    //enable overall interrupt
}


/***
  * ���ܣ�
        ��ʼ������
  * ������
        ��
  * ���أ�
        ��
  * ��ע��
***/
void init(void)
{	
	unsigned char temp = 0;
	
	WDT &= 0x7f;
    WDT |= 0xdf;
	FALL = OFF;
	RISE = OFF;
	BACK = OFF;
	AHEAD = OFF;
	EA = 0;
	
	while((!L1)&&(L3))
    {
		//AHEAD = ON;
		if(temp < 3)
		{
			BUZZ = ON;
			delay_ms(50);
			BUZZ = OFF;
			delay_ms(50);
			temp++;
		}
		RstWDT();
		WDT_CLR();
		if(temp == 3)
		{
			if((!S1)&&(!S2))
			{
				FALL = OFF;
				RISE = ON;		
			}
			else
			{
				FALL = OFF;
				RISE = OFF;
			}
			if((!S3)&&(!S2))
			{
				BACK = OFF;
				AHEAD = ON;	
			}
			else
			{
				BACK = OFF;
				AHEAD = OFF;
			}
		}
	}

	FALL = OFF;
	RISE = OFF;
	BACK = OFF;
	AHEAD = OFF; 
	if(temp == 3)
	{
		BUZZ = ON;
		delay_ms(100);
		BUZZ = OFF;
		while(1)
		{
			RstWDT();
			WDT_CLR();
		}
	}
	//reset back or forward motor to zero
	temp = RdB5045(SET_ADDR);
	if(temp ==SET_TRUE)
	{
		WDT_CLR();
		RstWDT();
		uiSet_Value = RdB5045(SET_ADDR_L);
		WDT_CLR();
		RstWDT();
		uiSet_Value += (unsigned int)(RdB5045(SET_ADDR_H))<<8;	
	}
	
	WDT_CLR();
	RstWDT();
	Timer0_init();
	uart_init();
	WDT_CLR();
	RstWDT();
	interrupt_init();
	
	if(L3)
	{
		bFisrt_Init = TRUE;
	}
}
