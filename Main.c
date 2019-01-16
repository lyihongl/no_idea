#include<stdio.h>
#include<stdlib.h>
#include "log.h"

int main();

void draw(int x, int y, char px);

int main()
{
	draw(3, 3, '#');
	return 0;
}

void draw(int x, int y, char px)
{
	system("clear");
	for(int i = 0; i<x; i++)
	{
		for(int j = 0; j<x; j++)
		{
			printf("#");
		}
		printf("\r\n");
	}
	//printf("%c", px);
}
