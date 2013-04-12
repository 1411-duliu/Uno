#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H 
void addMsg(char * msg);
void delMsg();
void printMsg();
void printUI();
DWORD WINAPI userInterfaceThread(LPVOID pM);
#endif