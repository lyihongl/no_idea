#include <windows.h>

short kbhit();

short kbhit(int vKey)
{
	if(GetAsyncKeyState(vKey))
	{
		return 1;
	}
	return 0;
}

short key_pressed(int vKey)
{
	short key_released = 1;
	if(kbhit(vKey))
	{
		if(key_released)
		{
			key_released = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
