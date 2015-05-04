#include"SST89x5x4.h"
#include "main.h"
#include "init.h"
#include "motor.h"
#include "key.h"
#include "X5045.h"
#include "uart485.h"
static unsigned char ucBuzz_Delay = BUZZ_TIMER;
static unsigned char ucMotor_Delay = 0x00;
unsigned int uiBack_Delay = 0x00;
unsigned int uiBack_Delay_Buff = 0x00;
static unsigned char ucStore_Warn = 0x00;
static unsigned int uiStore_Buff = 0x00;
static unsigned char ucBuzzCount = 0x03;
unsigned char ucSwitch_Mode = 0x55;          //init mode,the motor can't auto moving
unsigned char ucMotor_RuningMode = 0x55;      //lift motor runing ,0xaa,back ahead motor runing
bit bBuzz_On = FALSE; 
bit bMotor_Reverse = FALSE;
bit bMotor_Run = FALSE;
bit bBack_Enable = TRUE;              //back motor run enable
bit bMotor1_ON = FALSE;
bit bJump_Lock = TRUE;

unsigned char ucC6_Enable = 0x55;
//----------------------------------------
//
//----------------------------------------
void Buzz_On (unsigned char count)
{
	unsigned char _i = 0;
	for(_i = 0;_i < count; _i++)
	{
		BUZZ = 0;
		delay_ms(20);
		BUZZ = 1;
		delay_ms(20);
	}
	BUZZ = 1;

}
//----------------------------------------
//
//----------------------------------------
void Data_Strore(void)
{
	if(ucStore_Warn >= 100)
	{
		if(L1&&L3)
		{
			if((BACK)&&(AHEAD))
			{
				if(uiStore_Buff != uiBack_Delay)
	 	    	{
					WrB5045(SET_TRUE,SET_ADDR);
					RstWDT();
					WDT_CLR();
					WrB5045((uiBack_Delay&0xff),SET_ADDR_L);
					RstWDT();
					WDT_CLR();
					WrB5045((uiBack_Delay>>8),SET_ADDR_H);
					RstWDT();
					WDT_CLR();
					ucStore_Warn = 0x00;
					bBuzz_On = TRUE;
					uiStore_Buff = uiBack_Delay;
		 		    uiSet_Value = uiBack_Delay;
					ucBuzzCount = 3;
					Buzz_On(2);
				}
			}
			else
			{
					BACK = OFF;
					AHEAD = OFF;
			}
		}
		if(L1&&(!L3))
		{
			RstWDT();
			WDT_CLR();
			if(RdB5045(SET_ADDR) == SET_TRUE);
			{
				RstWDT();
				WDT_CLR();
				WrB5045(0x00,SET_ADDR);
				BUZZ = 0;
				delay_ms(20);
				BUZZ = 1;
				delay_ms(20);
				BUZZ = 0;
				delay_ms(20);
				BUZZ = 1;
				uiSet_Value = B_VALUE;
			}
			
			ucStore_Warn = 0x00;
		}
		
	}
}
//----------------------------------------
//
//----------------------------------------
void Back_Motor(void)
{
	WDT_CLR();
	RstWDT();
	if(uiBack_Delay < C_VALUE)
	{
		if(!bFisrt_Init)
		{
			BACK = S1;
			if(!S1)
			{
				ucMsg = 0x00;
				uiBack_Delay++;
				AHEAD = OFF;
				ucMotor_RuningMode = 0x55;	
				uiI1_MotorDelay = uiBack_Delay;
			}
		}
	}
	else
	{
		BACK = OFF;
	}
	if(uiBack_Delay > 0)
	{
		uiBack_Delay_Buff = 0x00;
		if(L3)
		{
			ucSwitch_Mode = 0xaa;       //按键功能失效
			AHEAD = S3;
			if(!S3)
			{
				ucMsg = 0x00;
				uiBack_Delay--;
				BACK = OFF;
				ucMotor_RuningMode = 0x55;
				uiI1_MotorDelay = uiBack_Delay;
									//bBack_Enable = FALSE;
			}

		}
		else
		{
			AHEAD = OFF;
			uiBack_Delay = 0x00;
			if(S3)
			{
				bMotor1_ON = TRUE;
			}
			if(bMotor1_ON)
			{
				ucSwitch_Mode = 0x55;
				bMotor1_ON = FALSE;
			}
		}
		
	}
	else
	{
		if(L3)
		{
			AHEAD = S3;
		}
		else
		{
			AHEAD = OFF;
			uiBack_Delay = 0x00;
			if(S3)
			{
				bMotor1_ON = TRUE;
				ucSwitch_Mode = 0x55;         //上升下降模式
			}
			if(bMotor1_ON)
			{
				ucSwitch_Mode = 0x55;
				bMotor1_ON = FALSE;
			}
		}
	}
	if(!S2)
	{
		ucMsg = 0x00;
		ucStore_Warn++;
	}
	else
	{
		if((ucStore_Warn>1)&&(ucStore_Warn<50))
		{
			BACK = OFF;
			AHEAD = OFF;
		}
		ucStore_Warn = 0x00;
	}
	if(!L3)
	{
		if(S3)
		{
			ucSwitch_Mode = 0x55;
		}
	}
}
//----------------------------------------
//
//----------------------------------------
void timer0_isr(void) interrupt 1
{
	TR0 = 0;
	TL0 = (RELOAD_VALUE&0x00ff);
	TH0 = ((RELOAD_VALUE>>8)&0x00ff);  //reload the count value
	TR0 = 1;
	RstWDT();
	WDT_CLR();
			if(!K8)
			{
				C6 = 0;
			}
			else
			{
				if(!C7)
				{
					ucLEDMsg = C6NULL_MSG;
					if(bC6_CTRL) 
					{
						if(ucC6_Enable == 0xaa)
						{
							ucC6_Enable = 0x55;
						}
						else
						{
							ucC6_Enable = 0xaa;
						}
						bC6_CTRL = 0;
					}
				}
				else
				{
					bC6_CTRL = 1;
					switch(ucLEDMsg)
					{
						case C6ON_MSG:
							C6 = 0;
							//ucMsg = C6NULL_MSG;
							break;
						case C6OFF_MSG:
							C6 = 1;
							//ucMsg = C6NULL_MSG;
							break;
						default:
							if(ucC6_Enable == 0xaa)
							{
								C6 = 0;
							}
							else
							{
								C6 = 1;
							}
							break;
					}
				}
			}
	if(I1&&I2)
	{
			bJump_Lock = TRUE;
			if((L1)&&(L2))                  
			{
				if(!(--ucBuzz_Delay))
				{
					BUZZ = ~BUZZ;
					ucBuzz_Delay = BUZZ_TIMER;
		    		}

			}                        // 如果线断开了
			if(L1)
			{
				if(bBack_Enable)
				{
					//ucMsg = 0x00;
					ucSwitch_Mode = 0xaa;
					if((!S1)||(!S2)||(!S3))
					{
						bBack_Enable = FALSE;
						ucMsg = 0x00;
					}
					if(ucMotor_RuningMode == 0xaa)
					{
						if(!bFisrt_Init)
						{
							BACK = ON;
						}
						uiBack_Delay++;
						if(uiBack_Delay == uiSet_Value)
						{
							bBack_Enable = FALSE;           //back motor 
							BACK = OFF;
							ucMotor_RuningMode = 0x55;
							
						}
						uiI1_MotorDelay = uiBack_Delay;
					}
					else
					{
						bBack_Enable = FALSE;
					}
				}
				else
				{
					
					//ucSwitch_Mode = 0xaa;
					Back_Motor();
				}
				
			 }
			else
			{
				uiBack_Delay = 0x00;
				BACK = OFF;
				AHEAD = OFF;
				ucMotor_RuningMode = 0x55;
				bBack_Enable = TRUE;                   //enable the back motor when the L1 if low
			}
			
	}
	else
	{
		ucMsg = 0x00;
			
		if(bJump_Lock)
		{
			ucKey_Status = SHOCK_ON;
			if(!bMotor_Reverse)
			{
					
					if(!I1)
					{
						I1_enable();
					}
					else
					{
						I2_enable();
					}
			}
		}
		else
		{
			if(ucKey_Status == 0x02)
			{
				motor_close();
			}
		}
	}
	if(!L4)
	{
			bMotor_Reverse = TRUE;
			bJump_Lock = FALSE;
	}
		if(bMotor_Reverse)
		{
			if(ucMotor_Delay == 0x00)
			{
				switch(ucKey_Status)
				{
					case 0x01:  
							ucKey_Status = 0x03;              //反转
							motor_fall();
							Buzz_On(3);
							break;
						case 0x02: 
							//motor_close();
							break;
						case 0x03: 
								ucKey_Status = 0x01;             //反转
								motor_rise();
								Buzz_On(3);
								break;
						case 0x00:  
								switch(ucMsg)
								{
									case RISE_MSG:
										ucMsg = FALL_MSG;
										Buzz_On(3);
										break;
									case STOP_MSG:
										break;
									case FALL_MSG:
										ucMsg = RISE_MSG;
										Buzz_On(3);
										break;
									default :
										break;
								}
								break;
						case SHOCK_ON:
								if(!I1)
								{
									ucMsg = FALL_MSG;
									Buzz_On(3);
								}
								else
								{
									if(!I2)
									{
										ucMsg = RISE_MSG;
										Buzz_On(3);
									}
									else
									{
										ucMsg = STOP_MSG;
									}
								}
								break;
						default: 
								break;
					}
						ucMotor_Delay = MOTOR_DELAY;
						bMotor_Run = TRUE;
				}
				else
				{
					if(L1||L2)
					{
						if(S1&&S3)
						{
							bMotor_Reverse = FALSE;
						}
						ucKey_Status = 0x02;
						bMotor_Run = FALSE;
						ucMsg = STOP_MSG;
						ucMotor_Delay = 0x00;
					}
					else
					{
				 		ucMotor_Delay--;
					}
					bJump_Lock = FALSE;
					if((ucMotor_Delay == 0x00)&&bMotor_Run)
					{
						if(S1&&S3)
						{
							bMotor_Reverse = FALSE;
						}
						ucKey_Status = 0x02;
						bMotor_Run = FALSE;
						ucMsg = STOP_MSG;
					}				 
				}
	}
	Msg_deal();
	
	
}

