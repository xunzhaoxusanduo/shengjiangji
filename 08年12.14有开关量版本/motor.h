#ifndef _MOTOR_
#define _MOTOR_
void motor_rise(void);
void motor_fall(void);
void motor_back(void);
void motor_ahead(void);
void motor_close(void);
void I1_enable(void);
void I2_enable(void);
sbit L1 = P0^6;
sbit L2 = P0^7;
sbit L4 = P2^6;
sbit L3 = P2^7;
#define BUZZ_TIMER 10
#define MOTOR_DELAY 200
extern unsigned int uiBack_Delay;
extern unsigned int uiI1_MotorDelay;
#endif
