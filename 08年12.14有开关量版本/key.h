#ifndef _KEY_
#define _KEY_
#define S1_ON 0x01                 //S1键按下
#define S2_ON 0x02                 //S2键按下
#define S3_ON 0x03                 //S3键按下
#define SHOCK_ON 0x04 
sbit S1 = P3^4;
sbit S2 = P3^5;
sbit S3 = P3^6;
sbit I1 = P3^2;
sbit I2 = P3^3;
void delay_ms(unsigned int i);
void GetKey_Status(void);
#endif