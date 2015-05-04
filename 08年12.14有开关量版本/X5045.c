#include "SST89x5x4.h"
#include "X5045.h"

//��λ���Ź�
void RstWDT()
{
    B_CS5045 = 0;
    B_CS5045 = 1;
}

//��X5045д�뵥�ֽ�����
//���룺x,��д����,address,д�����ݵĵ�ַ
void WrB5045(unsigned char x,unsigned char address) reentrant //����,��ַ
{
        wren();
        B_SCLK5045 = 0;
        B_CS5045 = 0;
        byteout(0x2); //write
        byteout(address);
        byteout(x);
        B_SCLK5045 = 0;
        B_CS5045 = 1;
        wip_chk();
        wrdi();
}

//��X5045���뵥�ֽ�����
//���룺address,�������ݵ�ַ
//���أ�����������
unsigned char RdB5045(unsigned char address)
{
        unsigned char data x;
        B_SCLK5045 = 0;
        B_CS5045 = 0;
        byteout(0x3);  //read 000h
        byteout(address);
        x = bytein();
        B_SCLK5045 = 0;
        B_CS5045 = 1;
        return (x);
}

//��X5045������ֽ�
void byteout(unsigned char x)
{
    unsigned char data i,j;
    j = 128;
    for(i = 0;i < 8;i++)
    {
        B_SCLK5045 = 0;
        B_SI5045 = x / j;
        B_SCLK5045 = 1;
        x %= j;
        j /= 2;
    }
    B_SI5045 = 0;
}

//�ȴ�X5045�����ڲ�д����
void wip_chk()
{
    unsigned char data dat;
    tcX5045 = 0;
 do
    {
        dat = rdsr();
        dat &= 0x1;
        if(tcX5045 >=5 ) break;
    }
    while(dat);
}

//5045״̬�Ĵ�����������
unsigned char rdsr()
{
    unsigned char data dat;
    B_SCLK5045 = 0;
    B_CS5045 = 0;
    byteout(5);
  	dat = bytein();
 	B_SCLK5045 = 0;
 	B_CS5045 = 1;
 	return (dat);
}

//��X5045����һ�ֽ�����
unsigned char bytein()
{
    unsigned char data i,x;
    x = 0;
    for (i = 0;i < 8;i++)
    {
        B_SO5045 = 1;
        B_SCLK5045 = 1;
        B_SCLK5045 = 0;
        if (B_SO5045) x = x + x +1;
        else x <<= 1;
    }
    return(x);
}

//5045״̬�Ĵ���д�����
void wrsr(unsigned char x)
{
    wren();
 	B_SCLK5045 = 0;
 	B_CS5045 = 0;
 	byteout(1);   //wrsr
 	byteout(x);
 	B_SCLK5045 = 0;
 	B_CS5045 = 1;
 	wip_chk();
    wrdi();
}

//д����
void wren()
{
 	B_SCLK5045 = 0;
 	B_CS5045 = 0;
 	byteout(6);
 	B_SCLK5045 = 0;
 	B_CS5045 = 1;
}

//д��ֹ
void wrdi()
{
 	B_SCLK5045 = 0;
 	B_CS5045 = 0;
    byteout(4);
    B_SCLK5045 = 0;
 	B_CS5045 = 1;
}

