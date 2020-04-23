#include<reg52.h>
#include<intrins.h>
#define uint unsigned int 
#define uchar unsigned char
sbit dula = P2^6;//��ѡ��
sbit wela = P2^7;//λѡ��
sbit LED = P2^5;//��ˮ��
sbit buzz = P3^5;
uchar led = 0xaa;
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
	buzz = 0;//�رշ�����
	TMOD = 0x51;//���ù�����ʽ(������1����ʱ��0)
	TH0 = 15536/256;//��ȡ�߰�λ
	TL0 = 15536%256;//��ȡ�Ͱ�λ��һ���ж�Ϊ0.05s
	TH1 = 0;
	TL1 = 0;
	EA = 1;//�����ж�
	ET0 = 1;//����ʱ��0
	ET1 = 1;//��������1
	TR0 = 1;//������ʱ��0
	TR1 = 0;
	LED = 1;
	P0 = led;
	LED = 0;
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
			P0 = 0x00;//����
			delay(2);
		}
		if(num == 50) delay(100000);
	}
}
void T0_time() interrupt 1
{
	TH0 = 15536/256;//��ȡ�߰�λ
	TL0 = 15536%256;//��ȡ�Ͱ�λ��һ���ж�Ϊ0.05s
	t += 1;
	if(t == 20)
	{
		t = 0;
		num++ ;
		LED = 1;
	   	led = ~led;
		P0 = led;
		LED = 0;
		buzz = ~buzz;
	}	
}
