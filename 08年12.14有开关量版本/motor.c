#include"SST89x5x4.h"
#include "main.h"
#include "key.h"
#include "init.h"
#include "motor.h"
unsigned int uiI1_MotorDelay = 0x00; //偏转电机延时
//--------------------------------------
//
//--------------------------------------
void motor_rise(void)
{
	if(L3)
	{
		RISE = OFF;
		FALL = OFF;
	}
	else
	{
		if(L1)
		{
				RISE = OFF;
				FALL = OFF;	
		}
		else
		{
				RISE = ON;
				FALL = OFF;
				ucMotor_RuningMode = 0xaa;
		}
		bFisrt_Init = FALSE;
	}
}
//--------------------------------------
//
//--------------------------------------
void motor_fall(void)
{	
	if(L3)
	{
		RISE = OFF;
		FALL = OFF;
	}
	else
	{
		if(L2)
		{
			RISE = OFF;
			FALL = OFF;
		
		}
		else
		{
			RISE = OFF;
			FALL = ON;
			ucMotor_RuningMode = 0xaa;
		}
		bFisrt_Init = FALSE;
	}
}
//--------------------------------------
//
//--------------------------------------
void motor_back(void)
{	
	BACK = ON;
	AHEAD = OFF;		
}
//--------------------------------------
//
//--------------------------------------
void motor_ahead(void)
{	
	BACK = OFF;
	AHEAD = ON;	
}
//--------------------------------------
//
//--------------------------------------
void motor_close(void)
{	
		FALL = OFF;
		RISE = OFF;
		BACK = OFF;
		AHEAD = OFF;	
}//--------------------------------------
//
//--------------------------------------
void I1_enable(void)
{	
		if((!L1)&&(L3))
		{
			RISE = OFF;
			FALL = OFF;
			BACK = OFF;
			AHEAD = OFF;
		}
		else
		{
			if(L1)
			{
				RISE = OFF;
				FALL = OFF;
				if(uiI1_MotorDelay<B_VALUE)
				{
					if(!bFisrt_Init)
					{
						BACK = ON;
						AHEAD = OFF;
						uiI1_MotorDelay++;
					}
				}
				else
				{
					BACK = OFF;
					AHEAD = OFF;
				}
				uiBack_Delay = uiI1_MotorDelay;
			}
			else
			{
				RISE = ON;
				FALL = OFF;
				BACK = OFF;
				AHEAD = OFF;
			}
			if(!L3)
			{
				bFisrt_Init = FALSE;
			}
		}
}
//--------------------------------------
//
//--------------------------------------
void I2_enable(void)
{	
	static unsigned char ucTemp_DelBuff = 0x00;
		//uiI1_MotorDelay = 0x00;
		if((!L1)&&(L3))
		{
			RISE = OFF;
			FALL = OFF;
			BACK = OFF;
			AHEAD = OFF;
		}
		else
		{
			if(!L3)
			{
				ucTemp_DelBuff = 0x00;
				BACK = OFF;
				AHEAD = OFF;
				ucSwitch_Mode = 0x55;       //偏转电机到位置了，自动停止
				if(L2)
				{
					RISE = OFF;
					FALL = OFF;
				}
				else
				{
					RISE = OFF;
					FALL = ON;
				}
				uiI1_MotorDelay = 0x00;	
				bFisrt_Init = FALSE;
			}
			else
			{
				if(uiI1_MotorDelay >0)
				{
					uiI1_MotorDelay--;
					BACK = OFF;
					AHEAD = ON;
					RISE = OFF;
					FALL = OFF;
					uiBack_Delay = uiI1_MotorDelay;
				}
				else
				{
					BACK = OFF;
					AHEAD = ON;
					RISE = OFF;
					FALL = OFF;
					uiBack_Delay = uiI1_MotorDelay;
				}
				
			}
		}
}
