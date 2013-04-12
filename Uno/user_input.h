#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <windows.h>
DWORD WINAPI inputThread(LPVOID pM);
char * getInput();
int getColor();

#endif