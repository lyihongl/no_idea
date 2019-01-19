#include <windows.h>

short kbhit();
short key_pressed(int vKey, short *key_released);
short single_key_press(int vKey, short *key_released);

short kbhit(int vKey)
{
	if(GetAsyncKeyState(vKey))
	{
		return 1;
	}
	return 0;
}

short key_pressed(int vKey, short *key_released)
{
	if(kbhit(vKey))
	{
		if(*key_released)
		{
			*key_released = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

short single_key_press(int vKey, short *key_released)
{
	while(1)
	{
		if(kbhit(0x41))
		{
			if(*key_released)
			{
				printf("%d\r\n", key_released);
			}
			if(key_pressed(0x41, key_released))
			{
				*key_released = 0;
			}
		}
		else
		{
			*key_released = 1;
		}
	}
}
