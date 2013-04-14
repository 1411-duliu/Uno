#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "uno.h"
#include "utilities.h"

extern int main_state;
extern STATE game_state;

extern CARDSET CARDS[5];
extern CARDSET cards_to_play;

extern HANDLE inputMutex, messageListMutex;
extern MSGLISTNODEPTR msgListPtr;

extern CARD card;

void printCardsetSizes()
{
	printf("# �ƶ�ʣ�ࣺ %d | ", CARDS[0].size);
	for (int i = 1; i <= 4; i++)
	{
		printf("��� %d �� %d | ", i, CARDS[i].size);
	}
	printf("\n");
}

void addMsg(char * msg)
{
	WaitForSingleObject(messageListMutex, INFINITE);

	MSGLISTNODEPTR newPtr;

	newPtr = (MSGLISTNODEPTR)malloc(sizeof(MSGLISTNODE));
	newPtr->msg = (char *)malloc(sizeof(char) * strlen(msg));
	strcpy(newPtr->msg, msg);
	newPtr->nextPtr = NULL;

	if (msgListPtr == NULL)
	{
		msgListPtr = newPtr;
	}
	else
	{
		newPtr->nextPtr = msgListPtr;
		msgListPtr = newPtr;
	}

	ReleaseMutex(messageListMutex);
}

void delMsg()
{
	if (msgListPtr != NULL)
	{
		while (msgListPtr != NULL)
		{
			MSGLISTNODEPTR tmp;

			tmp = msgListPtr;
			msgListPtr = msgListPtr->nextPtr;
			tmp->nextPtr = NULL;
			free(tmp);
		}
	}

}

void printMsg()
{
	WaitForSingleObject(messageListMutex, INFINITE);
	MSGLISTNODEPTR currentPtr = msgListPtr, tmp;
	
	int count = 0;

	printf("��Ϣ�б�:\n");
	while (currentPtr != NULL && count < MAX_MSG_NUM)
	{
		printf("Msg: %s\n", currentPtr->msg);
		currentPtr = currentPtr->nextPtr;
		count++;
	}
	printf("----------------\n");

	ReleaseMutex(messageListMutex);
}

void printUI()
{
	printCardsetSizes();
	printf("# ��ǰ��ɫ �� %s \n", colorToStr(game_state.color));
	if (game_state.player == HUMAN)
	{
		// printGameState(game_state);
		printf("\n ��Ļغ�..\n"
				"=========================\n");
		printCardset(CARDS[game_state.player]);
		//if(cards_to_play.size > 0)
		//{
		//	printf("����Գ������ƣ�\n");
		//	printCardset(cards_to_play);
		//}
	}
	else
		printf("��ȴ���� %d ����...\n", game_state.player);
}

DWORD WINAPI userInterfaceThread(LPVOID pM)
{
	while (main_state != 6)
	{
		system("cls");
		printMsg();
		switch (main_state)
		{
			case ROUND_START:
				printUI();
				Sleep(100);
				while(main_state != PLAY_CARD);
				break;
		
			case PLAY_CARD:
				printUI();
				Sleep(1000);
				
				WaitForSingleObject(inputMutex, INFINITE);
				break;

			case SETTLE:
				printf("��� %d ����� %s.\n", game_state.player, cardToStr(card));
				while (main_state != ROUND_END) 
				{
					Sleep(100);
				}
				// printf("����غϽ�����");
				break;

			case ROUND_END:
				Sleep(10);
				while (main_state == ROUND_END);
				printf("���غϽ����������� %d ��ҳ��ơ�", game_state.player);
				Sleep(1000);
				break;

			case GAME_END:
				Sleep(10);
				printf("\n��� %d Ӯ���˱��ֱ�����\n", game_state.player);
				main_state = 6;
				break;
		}
	}

	return 0;
}
