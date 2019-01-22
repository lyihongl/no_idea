#include<stdio.h>
#include<stdlib.h>
#include <sys\timeb.h>
#include "log.h"
#include "io.h"

#define X_SIZE 50
#define Y_SIZE 30

int main();

struct data_grid
{
	int x[X_SIZE];
	int y[Y_SIZE];
};

void init_grid(struct data_grid *grid);
void draw_grid(struct data_grid *grid);
void edit_grid(struct data_grid *grid, int x, int y, int val);

int main()
{
	struct timeb start, end;
	short key_down[2] = {0, 0};
	short run = 1;
	ftime(&start);
	int delta_t = 0;
	int sum = 0;
	int frames = 0;
	while(run)
	{
		ftime(&end);	
		delta_t = (int)(1000.0*(end.time-start.time)+end.millitm-start.millitm);
		if(delta_t > 16)
		{
			frames++;
			sum+=delta_t;
			if(sum >= 1000)
			{
				//printf("%d \r\n", frames);
				ALOG("%d \r\n", frames);
				frames = 0;
				sum = 0;
			}
			ftime(&start);
			if(single_key_press(0x41, &key_down[0]))
			{
				//printf("working");
			}
			if(single_key_press(0x1b, &key_down[1]))
			{
				run = 0;
			}
		}
	}
	return 0;
}
void edit_grid(struct data_grid *grid, int x, int y, int val)
{
	if(val != 1 && val != 0)
	{
		return;
	}
	grid->x[x] = val;
	grid->y[y] = val;
}
void init_grid(struct data_grid *grid)
{
	for(int i = 0; i<Y_SIZE; grid->y[i] = 0, ++i);
	for(int i = 0; i<X_SIZE; grid->x[i] = 0, ++i);
}

void draw_grid(struct data_grid *grid)
{
	system("clear");
	for(int i = 0; i<Y_SIZE; i++)
	{
		for(int j = 0; j<X_SIZE; j++)
		{
			if(grid->x[j] && grid->y[i])
			{
				//printf("%d %d", i, j);
				printf("%c", '#');
			}
			else
			{
				printf("  ");
			}
		}
		printf("\r\n");
	}
}
