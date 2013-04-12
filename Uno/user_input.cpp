#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "uno.h"
#include "utilities.h"

char input[1000];

extern HANDLE mainThreadHandle;

extern HANDLE uiThread;
extern HANDLE inputMutex;

int change_color = 0;

DWORD WINAPI inputThread(LPVOID pM)
{
	strcpy(input, "");
	
	SuspendThread(mainThreadHandle);
	Sleep(100);
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
	change_color = 1;
	return strToColor(getInput());
}