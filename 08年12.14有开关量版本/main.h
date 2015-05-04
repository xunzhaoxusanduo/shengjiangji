#ifndef _MAIN_
#define _MAIN_
#define SET_TRUE 0xaa
#define SET_ADDR 0x55
#define SET_ADDR_L 0x0f
#define SET_ADDR_H 0x10
#define C_VALUE 360
#define B_VALUE 190
#define ON 0
#define OFF 1
#define TRUE 1
#define FALSE 0
sbit BUZZ = P0^5;
sbit FALL = P0^0;
sbit RISE = P0^1;
sbit BACK = P0^3;
sbit AHEAD = P0^2;

sbit C6 = P0^4;
sbit K8 = P1^7;
sbit C7 = P2^5;
extern unsigned char ucKey_Status;
extern unsigned char ucSwitch_Mode;
extern unsigned char ucMotor_RuningMode ;
extern bit bMotor_Reverse;
extern bit bMotor_Run;
extern bit bC6_CTRL;
void Data_Strore(void);
#endif
