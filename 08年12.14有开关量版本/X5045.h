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
void WrB5045(unsigned char,unsigned char) reentrant;      //д�뵥�ֽ�����
unsigned char RdB5045(unsigned char);           //�������ֽ�����
void byteout(unsigned char);                    //��5045������ֽ�
void wip_chk(void);                             //�ȴ�5045�����ڲ�д����
unsigned char rdsr(void);                       //5045״̬�Ĵ�����������
unsigned char bytein(void);                     //��5045����һ�ֽ�����
unsigned char readx(void);                      //����ַ,��ַλ��100h
void wrsr(unsigned char);                       //5045״̬�Ĵ���д�����
void wren(void);                                //д����
void wrdi(void);                                //д��ֹ

#endif


