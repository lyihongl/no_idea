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
	int grid[X_SIZE][Y_SIZE];
};

struct snake_instance
{
	struct data_grid grid;
	int headx, heady;
};

void init_grid(struct data_grid *grid);
void draw_grid(struct data_grid *grid);
void edit_grid(struct data_grid *grid, int x, int y, int val);
void update(struct snake_instance * snake);
void init_game(struct snake_instance * snake);

int main()
{
	//for key the keyboard input system
	short key_down[16];

	short run = 1;

	struct snake_instance *snake_game = (struct snake_instance*)malloc(sizeof(struct snake_instance));
		
	//snake_game->grid = (struct data_grid*)malloc(sizeof(struct data_grid));
	init_game(snake_game);

	//fps keeping and game loop
	struct timeb start, end;
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
			draw_grid(&(snake_game->grid));
			frames++;
			sum+=delta_t;
			if(sum >= 1000)
			{
				ALOG("%d \r\n", frames);
				frames = 0;
				sum = 0;
			}
			ftime(&start);
			if(single_key_press(0x41, &key_down[0]))
			{
				edit_grid(&(snake_game->grid), snake_game->headx, snake_game->heady, 0);
				snake_game->headx++;
				edit_grid(&(snake_game->grid), snake_game->headx, snake_game->heady, 1);
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
	grid->grid[x][y] = val;
}
void init_grid(struct data_grid *grid)
{
	ALOG("2: %p \r\n", grid);
	//grid = (struct data_grid*)malloc(sizeof(struct data_grid));
	for(int i = 0; i<Y_SIZE; i++)
	{
		for(int j = 0; j<X_SIZE; j++)
		{
			grid->grid[j][i] = 0;
		}
	}
}

void draw_grid(struct data_grid *grid)
{
	system("clear");
	for(int i = 0; i<Y_SIZE; i++)
	{
		for(int j = 0; j<X_SIZE; j++)
		{
			if(grid->grid[j][i])
			{
				//printf("%d %d", i, j);
				printf("%c", '#');
			}
			else
			{
				printf(" ");
			}
		}
		printf("\r\n");
	}
}

void init_game(struct snake_instance *snake)
{
	ALOG("1: %p \r\n", &(snake->grid));
	init_grid(&(snake->grid));
	snake->headx = 3;
	snake->heady = 3;
	for(int i = 0; i<Y_SIZE; i++)
	{
		edit_grid(&(snake->grid), 0, i, 1);
		edit_grid(&(snake->grid), X_SIZE-1, i, 1);
	}
	for(int i = 0; i<X_SIZE; i++)
	{
		edit_grid(&(snake->grid), i, 0, 1);
		edit_grid(&(snake->grid), i, Y_SIZE-1, 1);
	}
	edit_grid(&(snake->grid), snake->headx, snake->heady, 1);
	//printf("%d %d \r\n", snake->grid.x[1], snake->grid.y[1]);
}

void update(struct snake_instance *snake)
{

}
