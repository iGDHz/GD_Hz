#include<reg52.h>
#include<intrins.h>
#define uint unsigned int 
#define uchar unsigned char
sbit dula = P2^6;//段选端
sbit wela = P2^7;//位选端
uchar code table[] = {
0x3f,0x06,0x5b,0x4f,0x66,
0x6d,0x7d,0x07,0x7f,0x6f
};
uint t = 0;
uint num = 0;
void delay(uint xms)
{
	int i,j;
	for(i = xms; i > 0; i--)
	{
		for(j = 250; j > 0; j--)
		{
			;
		}
	}
}
void main()
{
	uint temp;
	int i;
	uchar wei,times[6] = {0};
	TMOD = 0x01;//设置工作方式
	TH0 = 15536/256;//获取高八位
	TL0 = 15536%256;//获取低八位，一次中断为0.05s
	EA = 1;//开总中断
	ET0 = 1;//开定时器0
	TR0 = 1;//启动定时器0
	while(1)
	{
		temp = num;
		i = 5;
		while(i)	
		{
			times[i--] = temp%10;
			temp /= 10;
		}
		wei = 0xdf;
		for(i = 5; i >= 0; i--)
		{
			dula = 1;
			P0 = table[times[i]];
			dula = 0;
			wela = 1;
			P0 = wei;
			wela = 0;
			wei = _crol_(wei,-1);
			P0 = 0x00;//消隐
			delay(2);
		}
		
	}
}
void T0_time() interrupt 1
{
	TH0 = 15536/256;//获取高八位
	TL0 = 15536%256;//获取低八位，一次中断为0.05s
	t += 1;
	if(t == 20)
	{
		t = 0;
		num += 1;
	}
	if(num>999999) num = 0;	//错过范围清零
}