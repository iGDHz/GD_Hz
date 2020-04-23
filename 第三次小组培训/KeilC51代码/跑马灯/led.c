#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
unsigned int a;
uchar led;
void delay()
{
	uint x,y;
	for(x=100;x>0;x--)
	{
		for(y=250;y>0;y--)
		{
			 ;
		}	
	}	
}
void main()
{
	led = 0x55;
	while(1)
	{
		P0 = led;
		delay();
		led = _crol_(led,1);
	}
}