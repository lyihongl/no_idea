#include<stdio.h>
#include<stdlib.h>
#include <sys\timeb.h>
#include "log.h"
#include "io.h"

#define X_SIZE 80
#define Y_SIZE 40

int main();

struct data_grid
{
	int grid[X_SIZE][Y_SIZE];
};

struct snake
{
	int headx;
	int heady;
};

struct snake_instance
{
	struct data_grid grid;
	int length;
	//int headx, heady;
	struct snake game_snake[500];
};

enum direction
{
	left, right, up, down
};

void init_grid(struct data_grid *grid);
void draw_grid(struct data_grid *grid);
void edit_grid(struct data_grid *grid, int x, int y, int val);
void update(struct snake_instance * snake, enum direction dir, int *current_loc);
void init_game(struct snake_instance * snake);

int main()
{
	//for key the keyboard input system
	short key_down[16];

	short run = 1;

	struct snake_instance *snake_game = (struct snake_instance*)malloc(sizeof(struct snake_instance));

	enum direction dir;
		
	//snake_game->grid = (struct data_grid*)malloc(sizeof(struct data_grid));
	init_game(snake_game);

	//fps keeping and game loop
	struct timeb start, end;
	ftime(&start);
	int delta_t = 0;
	int sum = 0;
	int frames = 0;
	int current_loc = snake_game->length;

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
			edit_grid(&(snake_game->grid), snake_game->game_snake[0].headx, snake_game->game_snake[0].heady, 0);
			ftime(&start);
			if(single_key_press(0x41, &key_down[0])) 
			{
				dir = left;
			}
			if(single_key_press(0x44, &key_down[1]))
			{
				dir = right;
			}
			if(single_key_press(0x57, &key_down[2]))
			{
				dir = up;
			}
			if(single_key_press(0x53, &key_down[3]))
			{
				dir = down;
			}
			if(single_key_press(0x1b, &key_down[15]))
			{
				run = 0;
			}
			//switch(dir)
			//{
			//	case left: snake_game->game_snake[0].headx-=2;
			//	break;
			//	case right: snake_game->game_snake[0].headx+=2;
			//	break;
			//	case up: snake_game->game_snake[0].heady--;
			//	break;
			//	case down: snake_game->game_snake[0].heady++;
			//	break;
			//}

			//if(snake_game->game_snake[0].heady>=Y_SIZE-1)	{ snake_game->game_snake[0].heady = 1;}
			//if(snake_game->game_snake[0].heady<1)			{ snake_game->game_snake[0].heady = Y_SIZE-2;}
			//if(snake_game->game_snake[0].headx>=X_SIZE-1)	{ snake_game->game_snake[0].headx = 1;}
			//if(snake_game->game_snake[0].headx<1)			{ snake_game->game_snake[0].headx = X_SIZE-2;}
			ALOG("%p \r\n", snake_game);
			ALOG("current loc ad: %p \r\n", &current_loc);
			update(snake_game, dir, &current_loc);
			ALOG("snake instace ad 2: %p \r\n", snake_game);
			ALOG("current loc 3: %d \r\n", current_loc);
			for(int i = 0; i<10; i++)
			{
				printf("snake head here: %d %d %d \r\n", snake_game->game_snake[i].headx, snake_game->game_snake[i].heady, snake_game->grid.grid[snake_game->game_snake[i].headx][snake_game->game_snake[i].heady]);
			}
			//edit_grid(&(snake_game->grid), snake_game->game_snake[0].headx, snake_game->game_snake[0].heady, 1);
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
	snake->game_snake[0].headx = 3;
	snake->game_snake[0].heady = 3;
	snake->length = 10;
	for(int i = 0; i<snake->length; i++)
	{
		snake->game_snake[i].headx = snake->game_snake[0].headx+i;
		snake->game_snake[i].heady = snake->game_snake[0].heady;
	}
	for(int i = 0; i<snake->length; i++)
	{
		edit_grid(&(snake->grid), snake->game_snake[i].headx, snake->game_snake[i].heady, 1);
	}
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
	edit_grid(&(snake->grid), snake->game_snake[0].headx, snake->game_snake[0].heady, 1);
	//printf("%d %d \r\n", snake->grid.x[1], snake->grid.y[1]);
}

void update(struct snake_instance *snake, enum direction dir, int *current_loc)
{
	ALOG("%p \r\n", snake);
	ALOG("snake instance ad: %p \r\n", snake);
	int length = snake->length;
	printf("%d %d \r\n", snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady);
	ALOG("current loc: %d \r\n", *current_loc);
	ALOG("current loc ad: %p \r\n", current_loc);
	
	//edit_grid(&(snake->grid), snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady, 0);
	int head;
	if(*current_loc == length-1)
	{
		head = 0;
	}
	else
	{
		head = *current_loc+1;
	}

	if(dir == right)
	{
		snake->game_snake[*current_loc].headx = snake->game_snake[head].headx+1;
		snake->game_snake[*current_loc].heady = snake->game_snake[head].heady;
	}
	else if(dir == left)
	{
		snake->game_snake[*current_loc].headx = snake->game_snake[head].headx-1;
		snake->game_snake[*current_loc].heady = snake->game_snake[head].heady;
	}
	else if(dir == up)
	{
		snake->game_snake[*current_loc].heady = snake->game_snake[head].heady-1;
		snake->game_snake[*current_loc].headx = snake->game_snake[head].headx;
	}
	else
	{
		snake->game_snake[*current_loc].heady = snake->game_snake[head].heady+1;
		snake->game_snake[*current_loc].headx = snake->game_snake[head].headx;
	}
	edit_grid(&(snake->grid), snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady, 1);
	if(snake->game_snake[*current_loc].heady>=Y_SIZE-1)	{ snake->game_snake[*current_loc].heady = 1;}
	if(snake->game_snake[*current_loc].heady<1)			{ snake->game_snake[*current_loc].heady = Y_SIZE-2;}
	if(snake->game_snake[*current_loc].headx>=X_SIZE-1)	{ snake->game_snake[*current_loc].headx = 1;}
	if(snake->game_snake[*current_loc].headx<1)			{ snake->game_snake[*current_loc].headx = X_SIZE-2;}
	*current_loc = *current_loc - 1;
	ALOG("current loc 2: %d \r\n", *current_loc);

	if(*current_loc < 0)
	{
		LOG("THIS SHOULDNT BE RUNNINNG");
		*current_loc = length-1;
	}
}
