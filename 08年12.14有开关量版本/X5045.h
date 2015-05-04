#ifndef X5045_h
#define X5045_h

#define WDT1_4  0x00;
#define WDT600  0x10;
#define WDT200  0x20;
#define WDTDIS  0x30;

//BIT
sbit B_CS5045 = P2^4;
sbit B_SO5045 = P2^3;
sbit B_SCLK5045 = P2^2;
sbit B_SI5045 = P2^1;

extern unsigned char data tcX5045;

void RstWDT(void);
void WrB5045(unsigned char,unsigned char) reentrant;      //写入单字节数据
unsigned char RdB5045(unsigned char);           //读出单字节数据
void byteout(unsigned char);                    //向5045输出单字节
void wip_chk(void);                             //等待5045结束内部写周期
unsigned char rdsr(void);                       //5045状态寄存器读出程序
unsigned char bytein(void);                     //从5045读出一字节数据
unsigned char readx(void);                      //读地址,地址位于100h
void wrsr(unsigned char);                       //5045状态寄存器写入程序
void wren(void);                                //写允许
void wrdi(void);                                //写禁止

#endif


