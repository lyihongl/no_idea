#include<stdio.h>
#include<stdlib.h>
#include <sys\timeb.h>
#include "log.h"
#include "io.h"
#include "util.h"

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
int update(struct snake_instance * snake, enum direction dir, int *current_loc);
void init_game(struct snake_instance * snake);
void spawn_food(struct data_grid *grid);
int detect_collision(struct data_grid *grid, int x, int y);
struct data_grid *copy_grid(struct data_grid *grid);

int main()
{
	//for key the keyboard input system
	short key_down[16];

	short run = 1;

	struct snake_instance *snake_game = (struct snake_instance*)malloc(sizeof(struct snake_instance));

	enum direction dir = down;
		
	//snake_game->grid = (struct data_grid*)malloc(sizeof(struct data_grid));
	init_game(snake_game);

	//fps keeping and game loop
	struct timeb start, end;
	ftime(&start);
	int delta_t = 0;
	int sum = 0;
	int frames = 0;
	int current_loc = snake_game->length-1;
	
	spawn_food(&(snake_game->grid));
	short first_run_passed = 0;

	while(run)
	{
		ftime(&end);	
		delta_t = (int)(1000.0*(end.time-start.time)+end.millitm-start.millitm);
		if(delta_t > 8)
		{
			draw_grid(&(snake_game->grid));
			frames++;
			sum+=delta_t;
			if(sum >= 1000)
			{
				//snake_game->length = snake_game->length+1;	
				//printf("length %d", snake_game->length);
				ALOG("%d \r\n", frames);
				frames = 0;
				sum = 0;
			}
				//snake_game->length = snake_game->length+1;	
				//printf("length %d", snake_game->length);
			//edit_grid(&(snake_game->grid), snake_game->game_snake[0].headx, snake_game->game_snake[0].heady, 0);
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
			//spawn_food(NULL);
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
			if(update(snake_game, dir, &current_loc))
			{
				if(first_run_passed)
					run = 0;
			}
			first_run_passed = 1;
			ALOG("snake instace ad 2: %p \r\n", snake_game);
			ALOG("current loc 3: %d \r\n", current_loc);
			//for(int i = 0; i<10; i++)
			//{
			//	printf("snake head here: %d %d %d \r\n", snake_game->game_snake[i].headx, snake_game->game_snake[i].heady, snake_game->grid.grid[snake_game->game_snake[i].headx][snake_game->game_snake[i].heady]);
			//}
			//edit_grid(&(snake_game->grid), snake_game->game_snake[0].headx, snake_game->game_snake[0].heady, 1);
		}
	}
	return 0;
}
void edit_grid(struct data_grid *grid, int x, int y, int val)
{
	if(val > 3 || val < 0)
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
	//TODO: find the print statement and remove it, finish this
	//system("clear");
	//cls();
	//struct data_grid *current_grid = grid;
	struct data_grid *previous_grid = NULL;
	int difference_grid[X_SIZE][Y_SIZE] = {0};
	if(previous_grid != NULL)
	{
		for(int i = 0; i<X_SIZE; i++)
		{
			for(int j = 0; j<Y_SIZE; j++)
			{
				if(grid->grid[i][j] != previous_grid->grid[i][j])
				{

				}
			}
		}
	}
	free(previous_grid);
	previous_grid = copy_grid(grid);
	//previous_grid = current_grid;
	//for(int i = 0; i<Y_SIZE; i++)
	//{
		//for(int j = 0; j<X_SIZE; j++)
		//{
			//if(grid->grid[j][i] == 1)
			//{
				////printf("%d %d", i, j);
				//printf("%c", '#');
			//}
			//else if(grid->grid[j][i] == 3)
			//{
				//printf("%c", 'x');
			//}
			//else if(grid->grid[j][i] == 2)
			//{
				//printf("%c", '@');
			//}
			//else
			//{
				//printf(" ");
			//}
		//}
		//printf("\r\n");
	//}
}

struct data_grid *copy_grid(struct data_grid *grid)
{
	struct data_grid *new_grid = (struct data_grid*)(malloc(sizeof(struct data_grid)));
	for(int i = 0; i<X_SIZE; i++)
	{
		for(int j = 0; j<Y_SIZE; j++)
		{
			new_grid->grid[i][j] = grid->grid[i][j];
		}
	}
	return new_grid;
}

void init_game(struct snake_instance *snake)
{
	ALOG("1: %p \r\n", &(snake->grid));
	init_grid(&(snake->grid));
	snake->game_snake[0].headx = 5;
	snake->game_snake[0].heady = 5;
	snake->length = 3;
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
		edit_grid(&(snake->grid), 0, i, 3);
		edit_grid(&(snake->grid), X_SIZE-1, i, 3);
	}
	for(int i = 0; i<X_SIZE; i++)
	{
		edit_grid(&(snake->grid), i, 0, 3);
		edit_grid(&(snake->grid), i, Y_SIZE-1, 3);
	}
	//edit_grid(&(snake->grid), snake->game_snake[0].headx, snake->game_snake[0].heady, 1);
	//printf("%d %d \r\n", snake->grid.x[1], snake->grid.y[1]);
}

int update(struct snake_instance *snake, enum direction dir, int *current_loc)
{
	ALOG("%p \r\n", snake);
	ALOG("snake instance ad: %p \r\n", snake);
	int length = snake->length;
	printf("length: %d", length);
	//printf("%d %d \r\n", snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady);
	ALOG("current loc: %d \r\n", *current_loc);
	ALOG("current loc ad: %p \r\n", current_loc);
	
	edit_grid(&(snake->grid), snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady, 0);
	//printf("v at h %d \r\n", snake->grid.grid[snake->game_snake[*current_loc].headx][snake->game_snake[*current_loc].heady]);
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
	printf("v at h %d \r\n", snake->grid.grid[snake->game_snake[*current_loc].headx][snake->game_snake[*current_loc].heady]);
	if(detect_collision(&(snake->grid), snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady) == 2)
	{
		length = ++snake->length;
		
		snake->game_snake[length-1].headx = snake->game_snake[*current_loc].headx;
		snake->game_snake[length-1].heady = snake->game_snake[*current_loc].heady;
		spawn_food(&(snake->grid));
	}
	else if(detect_collision(&(snake->grid), snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady) == 1){
		//printf("this isnt working");
		return 1;
	}
	//printf("%d, %d, %d \r\n", snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady, *current_loc);
	if(snake->game_snake[*current_loc].heady>=Y_SIZE-1)	{ snake->game_snake[*current_loc].heady = 1;}
	if(snake->game_snake[*current_loc].heady<1)			{ snake->game_snake[*current_loc].heady = Y_SIZE-2;}
	if(snake->game_snake[*current_loc].headx>=X_SIZE-1)	{ snake->game_snake[*current_loc].headx = 1;}
	if(snake->game_snake[*current_loc].headx<1)			{ snake->game_snake[*current_loc].headx = X_SIZE-2;}
	edit_grid(&(snake->grid), snake->game_snake[*current_loc].headx, snake->game_snake[*current_loc].heady, 1);
	*current_loc = *current_loc - 1;
	ALOG("current loc 2: %d \r\n", *current_loc);

	if(*current_loc == -1)
	{
		//LOG("THIS SHOULDNT BE RUNNINNG");
		*current_loc = length-1;
	}
	return 0;
}

void spawn_food(struct data_grid *grid)
{
	int x_rand = gen_rand(2, X_SIZE-2);
	int y_rand = gen_rand(2, Y_SIZE-2);
	
	edit_grid(grid, x_rand, y_rand, 2);
	//grid->grid[x_rand][y_rand] = 2;	
	//printf("food: %d %d \r\n", x_rand, y_rand);
}
int detect_collision(struct data_grid *grid, int x, int y)
{
	if(grid->grid[x][y]==2)
	{
		return 2;
	}
	if(grid->grid[x][y] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}