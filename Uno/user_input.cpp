#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "uno.h"
#include "ai_simple.h"
#include "user_interface.h"
#include "utilities.h"

char input[1000];

extern HANDLE mainThreadHandle;

extern HANDLE uiThread;
extern HANDLE inputMutex;

extern STATE game_state;
extern CARDSET CARDS[5];

int change_color = 0;

DWORD WINAPI inputThread(LPVOID pM)
{
	strcpy(input, "");
	
	SuspendThread(mainThreadHandle);
	Sleep(200);
	SuspendThread(uiThread);
	if (change_color) 
	{
		printf("使用了变色卡，请输入颜色(GREEN/BLUE/RED/YELLOW)：\n");
		change_color = 0;
	}

	printf("> ");
	
	while (strlen(input) == 0)
	{
		scanf("%s", input);
	}
	ResumeThread(uiThread);
	ResumeThread(mainThreadHandle);

	return 0;
}

char * getInput()
{
	inputMutex = CreateMutex(NULL, TRUE, NULL);
	HANDLE handle = CreateThread(NULL, 0, inputThread, NULL, 0, NULL);
	WaitForSingleObject(handle, INFINITE);
	ReleaseMutex(inputMutex);
	

	return input;
}

int getColor()
{
	int color;

	char msg[20];

	if (game_state.player == HUMAN)
	{
		change_color = 1;
		color = strToColor(getInput());
	}
	else
		color = chooseColor(CARDS[game_state.player]);

	strcpy(msg, "颜色变为： ");
	int length = strlen(msg);
	strcpy(msg + length, colorToStr(color));
	length = strlen(msg);
	strcpy(msg + length, "\0");  
	addMsg(msg);

	return color;
}