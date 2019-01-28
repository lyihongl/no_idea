#include <time.h>
#include <stdlib.h>
int gen_rand(int min, int max);

int gen_rand(int min, int max)
{
	srand(time(NULL));
	return rand() % (max-min) + min;
}
