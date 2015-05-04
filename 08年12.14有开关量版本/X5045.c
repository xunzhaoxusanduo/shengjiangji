#include "SST89x5x4.h"
#include "X5045.h"

//复位看门狗
void RstWDT()
{
    B_CS5045 = 0;
    B_CS5045 = 1;
}

//向X5045写入单字节数据
//输入：x,待写数据,address,写入数据的地址
void WrB5045(unsigned char x,unsigned char address) reentrant //数据,地址
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

//从X5045读入单字节数据
//输入：address,待读数据地址
//返回：读出的数据
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

//向X5045输出单字节
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

//等待X5045结束内部写周期
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

//5045状态寄存器读出程序
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

//从X5045读出一字节数据
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

//5045状态寄存器写入程序
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

//写允许
void wren()
{
 	B_SCLK5045 = 0;
 	B_CS5045 = 0;
 	byteout(6);
 	B_SCLK5045 = 0;
 	B_CS5045 = 1;
}

//写禁止
void wrdi()
{
 	B_SCLK5045 = 0;
 	B_CS5045 = 0;
    byteout(4);
    B_SCLK5045 = 0;
 	B_CS5045 = 1;
}

