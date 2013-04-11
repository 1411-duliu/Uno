#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "uno.h"
#include "utilities.h"

char input[1000];

extern HANDLE inputMutex;

DWORD WINAPI inputThread(LPVOID pM)
{
	strcpy(input, "");

	while (strlen(input) == 0)
	{
		scanf("%s", input);
	}

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
	return strToColor(getInput());
}