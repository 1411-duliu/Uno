#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char input[1000];

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
	HANDLE handle = CreateThread(NULL, 0, inputThread, NULL, 0, NULL);
	WaitForSingleObject(handle, INFINITE);
	
	return input;
}