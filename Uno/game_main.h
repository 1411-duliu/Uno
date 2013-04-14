#ifndef GAME_M_H
#define GAME_M_H
void main_loop();
int getNextPlayer(STATE game_state);
DWORD WINAPI mainThread(LPVOID pM);

#endif