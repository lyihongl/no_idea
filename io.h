#include <windows.h>
#include "log.h"
short kbhit();
short single_key_press(int vKey, short *key_down);

short kbhit(int vKey)
{
	if(GetAsyncKeyState(vKey))
	{
		return 1;
	}
	return 0;
}

short single_key_press(int vKey, short *key_down)
{
	if(*key_down && kbhit(vKey))
	{
		return 0;
	}
	if(kbhit(vKey))
	{
		//LOG("hit");
		*key_down = 1;
		return 1;
	}
	else
	{
		*key_down = 0;
	}
	return 0;
}
