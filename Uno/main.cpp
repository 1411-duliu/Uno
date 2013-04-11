#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "uno.h"
#include "generate_card.h"
#include "cardset_process.h"
#include "card_process.h"
#include "utilities.h"
#include "user_input.h"

CARDSET CARDS[5];
STATE game_state;

CARDSET cards_to_play;

MSGLISTNODEPTR msgListPtr = NULL, msgListTailPtr = NULL;

HANDLE messageListMutex;
HANDLE inputMutex;

int main_state = 1;

CARD NONE_CARD = {CNONE, NONE};
CARD INVALID_CARD = {CNONE, INVALID};
CARD CALL_CARD = {CNONE, CALL};

void init_game()
{
	CARD * cards = generateCards();
    shuffleCards(cards);
	getIntoCardset(&CARDS[0], cards, 108);
	distributeCards(CARDS, CARDS[0], PLAYER_NUM);

	game_state = init_state();
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
		msgListTailPtr = msgListPtr;
	}
	else
	{
		msgListTailPtr->nextPtr = newPtr;
		msgListTailPtr = newPtr;
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
	
	printf("消息列表:\n");
	while (currentPtr != NULL)
	{
		printf("Msg: %s\n", currentPtr->msg);
		currentPtr = currentPtr->nextPtr;
		
	}
	printf("----------------\n");

	ReleaseMutex(messageListMutex);
}

DWORD WINAPI userInterfaceThread(LPVOID pM)
{
	while (main_state != GAME_END)
	{
		system("cls");
		switch (main_state)
		{
			case ROUND_START:
				printMsg();
				printf("你的手牌列表：\n");
				printCardset(CARDS[game_state.player]);
				Sleep(100);
				break;
		
			case PLAY_CARD:
				printMsg();

				printGameState(game_state);
				printf("你的手牌列表：\n");
				printCardset(CARDS[game_state.player]);
				printf("你可以出下列牌：\n");
				printCardset(cards_to_play);
				Sleep(100);
				WaitForSingleObject(inputMutex, INFINITE);
				break;
		}
	}

	return 0;
}

int main(int argc, const char * argv[])
{
	init_game();
	// printGameState(game_state);
	int player;

	HANDLE uiThread = CreateThread(NULL, 0, userInterfaceThread, NULL, 0, NULL);
	
	messageListMutex = CreateMutex(NULL, FALSE, NULL);
	

	while (main_state != GAME_END)
	{
		player = game_state.player;
		
		if (main_state == ROUND_START)
		{
			genCardsToPlay(&cards_to_play, game_state, CARDS[player]);
			printCardset(cards_to_play);
			if (hasThisCard(cards_to_play, NONE_CARD) && cards_to_play.size == 1)
			{
				// 如果可出的牌中只有1张NONE，那么不能出牌
				addMsg("本局不能出牌，进入结算阶段。");
				Sleep(2000);
				main_state = GAME_END; // 进入结算状态
				continue;
			}
			Sleep(3000);
			main_state = PLAY_CARD;
		}
		else if (main_state == PLAY_CARD)
		{
			CARD card;
			// 等待用户选择，如果选择不合法则循环。
			inputMutex = CreateMutex(NULL, TRUE, NULL);
			// WaitForSingleObject(inputMutex, INFINITE);
			while (!(isValid(card = genCard(getInput())) && hasThisCard(cards_to_play, card)))
			{
				addMsg("输入不合法，请重新输入。");
				ReleaseMutex(inputMutex);
				Sleep(1000);
				inputMutex = CreateMutex(NULL, TRUE, NULL);
			}
			
			
			printf("\nInput: %s\n", cardToStr(card));
			
			main_state = GAME_END;
			clearCardset(&cards_to_play);
			
			break;
		}
	}

	WaitForSingleObject(uiThread, INFINITE);
	CloseHandle(uiThread);
	CloseHandle(messageListMutex);

	system("pause");

    return 0;
}
