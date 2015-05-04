#include"SST89x5x4.h"
#include "main.h"
#include "init.h"
#include "motor.h"
#include "key.h"
#include "Uart485.h"
#include "X5045.h"
unsigned char ucRev_Buf[7];
bit bRev_Flag = FALSE;
unsigned char ucMsg = 0x00;

unsigned char ucLEDMsg = 0x00;
//----------------------------------------
//
//----------------------------------------
void Revdata_deal(void)
{
	
	if((ucRev_Buf[3] == (~P1))||(ucRev_Buf[3] == 0x00))
	{
			switch(ucRev_Buf[4])
			{

				case 0x00:
					ucMsg = STOP_MSG;
					break;
				case 0x01:
					if(ucRev_Buf[5] == 0x01)
					{
						ucMsg = RISE_MSG;
					}
					else
					{
						ucMsg = STOP_MSG;
					}
					break;
				case 0x02:
					if(ucRev_Buf[5] == 0x01)
					{
						ucMsg = FALL_MSG;
					}
					else
					{
						ucMsg = STOP_MSG;
					}
					break;
				case 0x05:                                                  //若要改成3，4，即可将case 0x05改成case 03,04即可
					if(ucRev_Buf[5] == 0x01)
					{
						ucLEDMsg = C6ON_MSG;
					}
					else
					{
						ucLEDMsg = C6OFF_MSG;
					}
					break;
				default :
					break;

			}
	}
}
//----------------------------------------
//
//----------------------------------------
void uart_isr(void) interrupt 4
{
	static unsigned char ptr = 0;
	unsigned char temp = 0;
	RstWDT();
	WDT_CLR();
	if (TI)
	{
		TI = 0;
	}
	if (RI)
	{
		RI = 0;
		temp = SBUF;
		if(bRev_Flag)
		{
			ucRev_Buf[ptr] = temp;
			ptr++;
			if(ptr == REV_LEN)
			{
				ptr = 0;
				bRev_Flag = FALSE;
				Revdata_deal();
				ucKey_Status = 0x00;
			}
		}
		else
		{
			if(temp == REV_HEAD)
			{
				ptr = 0;
				bRev_Flag = TRUE;
				ucRev_Buf[ptr] = temp;
				ptr++;
			}
		}
			
		
	}


}
//----------------------------------------
//
//----------------------------------------
void Msg_deal(void)
{
	switch(ucMsg)
	{

		case RISE_MSG:
			I1_enable();
			break;
		case STOP_MSG:
			motor_close();
			break;
		case FALL_MSG:
			I2_enable();
			break;
		default :
			break;
	}
}