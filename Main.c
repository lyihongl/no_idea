#include<stdio.h>
#include<stdlib.h>
#include "log.h"

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
