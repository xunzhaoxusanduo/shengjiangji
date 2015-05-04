#ifndef UART_485_H
#define  UART_485_H
#define REV_LEN  7
#define REV_HEAD 0xf6
#define RISE_MSG 0x22
#define FALL_MSG 0x11
#define STOP_MSG 0x33

#define C6ON_MSG 0x44
#define C6OFF_MSG 0x55
#define C6NULL_MSG 0x66
extern unsigned char ucMsg;
extern unsigned char ucLEDMsg;
void Msg_deal(void);
#endif
