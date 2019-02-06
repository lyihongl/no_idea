#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
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

void cls()
{
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = {0, 0};

	fflush(stdout);
	if(!GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;

	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(hOut, topLeft);
}
void set_cursor_position(int x, int y)
{

}