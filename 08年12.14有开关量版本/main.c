#include"SST89x5x4.h"
#include "main.h"
#include "key.h"
#include "init.h"
#include "X5045.h"
#include "motor.h"
#include "uart485.h"
sbit OUT_CTRL = P3^7;

bit bC6_CTRL = 1;
unsigned char ucKey_Status = 0x00;

//---------------------------------------------
//主函数
//---------------------------------------------
void main(void)
{
	unsigned char temp = 0;
	unsigned char temp1 = 0x00;
	unsigned int i = 0;

	init();
	
	while(1)
	{
		if(S3&&!L3)
		{
			ucSwitch_Mode = 0x55;         //上升下降模式
		}
		
		if((I1)&&(I2))
		{
			if(ucSwitch_Mode == 0x55)      //按键功能使能
			{
				WDT_CLR();
				RstWDT();
				GetKey_Status();
				if(!bMotor_Reverse)
				{
					switch(ucKey_Status)
					{
						case 0x01: 
							motor_rise();
							ucMsg = 0x00;
							break;
						case 0x02: 
							motor_close();
							ucMsg = 0x00;
							break;
						case 0x03: 
							motor_fall();
							ucMsg = 0x00;
							break;
						case 0x05: 
							break;
						case 0x00: 
							RstWDT();
							WDT_CLR();
							break;
						default: 
							break;
					}
				}
			}

			if(ucKey_Status == 0x04)
			{
				ucKey_Status = 0x00;
				motor_close();
			}
		}
		
		WDT_CLR();
		RstWDT();
		Data_Strore();
	}
}
