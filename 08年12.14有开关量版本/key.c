#include"SST89x5x4.h"
#include "main.h"
#include "key.h"
#include "init.h"
#include "X5045.h"

//--------------------------------------------------------------
//
//延时
//------------------------------------------------------------
void delay_ms(unsigned int i)
{
	unsigned int j;
	unsigned int k;
	for(k = 0;k < i; k++)
	{
		//RstWDT();
		WDT_CLR();
		for(j = 0;j <250;j++) RstWDT();
	}
}
//--------------------------------------------------------------
//
//获取按键
//------------------------------------------------------------
void GetKey_Status(void)
{
	if(!S1)
	{
		delay_ms(2);
		if(!S1)
		{
			ucKey_Status = S1_ON;
		}
	}
		if(!S2)
	{
		delay_ms(2);
		if(!S2)
		{
			ucKey_Status = S2_ON;
		}
	}
		if(!S3)
		{
			delay_ms(2);
			if(!S3)
			{
				ucKey_Status = S3_ON;
			}
	}
}
