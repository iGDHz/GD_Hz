#include<stdio.h>
#include<stdlib.h>


int main()
{
	int i;
	FILE *fp;
	srand((unsigned)time(NULL));
	fp = fopen("test_data","w");
	for(i = 0; i < 5000; i++)
	{
		fprintf(fp,"%d ", rand()%10000);
	}
	fclose(fp);
	return 0;
}
