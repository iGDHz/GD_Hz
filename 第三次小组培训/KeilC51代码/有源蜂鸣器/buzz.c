#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit buzz = P2^0;
void delay(uint xms)
{
	uint i,j;
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
	buzz = 1;
	while(1)
	{
		buzz = !buzz;
		delay(10);
	}
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       