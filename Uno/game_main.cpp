#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "uno.h"
#include "generate_card.h"
#include "ai_simple.h"
#include "cardset_process.h"
#include "card_process.h"
#include "utilities.h"
#include "user_input.h"
#include "func_card.h"
#include "log_write.h"
#include "user_interface.h"

CARDSET CARDS[5];
STATE game_state;

CARDSET cards_to_play;

MSGLISTNODEPTR msgListPtr = NULL;

HANDLE mainThreadHandle;
HANDLE uiThread;
HANDLE messageListMutex;
HANDLE inputMutex;

int main_state = 1;

CARD NONE_CARD = {CNONE, NONE};
CARD INVALID_CARD = {CNONE, INVALID};
CARD CALL_CARD = {CNONE, CALL};
CARD EMPTY_CARD = {0, 0};

CARD card;

void init_game()
{
	CARD * cards = generateCards();
    shuffleCards(cards);
	getIntoCardset(&CARDS[0], cards, 108);
	distributeCards(CARDS, CARDS[0], PLAYER_NUM);

	game_state = init_state();
	card = EMPTY_CARD;
	
}

int getNextPlayer(STATE game_state)
{
	int nplayer = game_state.player;

	if (game_state.direction == 1)
	{
		if (nplayer == PLAYER_NUM)
			nplayer = 1;
		else
			nplayer += 1;
	}
	else
		if (nplayer == 1)
			nplayer = PLAYER_NUM;
		else
			nplayer -= 1;

	return nplayer;
}


DWORD WINAPI mainThread(LPVOID pM)
{
	init_game();
	
	int player;

	uiThread = CreateThread(NULL, 0, userInterfaceThread, NULL, 0, NULL);
	messageListMutex = CreateMutex(NULL, FALSE, NULL);
	
	int call_flag = 0;

	while (main_state != GAME_END)
	{
		player = game_state.player;
		
		if (main_state == ROUND_START)
		{
			genCardsToPlay(&cards_to_play, game_state, CARDS[player]); // 生成本回合可以出的牌
			
			if (hasThisCard(cards_to_play, NONE_CARD) && cards_to_play.size == 1)
			{
				// 如果可出的牌中只有1张NONE，那么不能出牌
				addMsg("本局不能出牌，进入结算阶段。");
				card = NONE_CARD;
				Sleep(1000);
				main_state = SETTLE; // 进入结算状态
				continue;
			}

			if (call_flag) // 如果之前已经交过一次牌则把 CALL 从可出牌中删除
				deleteFromCardset(&cards_to_play, CALL_CARD);

			if (!cards_to_play.size) // 如果没有可出的牌（即在叫过一次牌后），则直接进入回合结束状态
			{
				main_state = ROUND_END;
				addMsg("没有可以出的牌，回合结束");
					
				continue;
			}
			
			Sleep(1000);
			main_state = PLAY_CARD; // 进入出牌阶段
		}
		else if (main_state == PLAY_CARD)
		{
			if (player == HUMAN)
			{
				while (!(isValid(card = genCard(getInput())) && hasThisCard(cards_to_play, card)))
				{
					addMsg("输入不合法，请重新输入。");
					Sleep(1000);
				}
			}
			else
			{
				Sleep(1000);
				card = AI_SIMPLE(&CARDS[player], &cards_to_play);
			}

			addMsg(playCardMsg(game_state.player, card));
			
			if (isSameCards(CALL_CARD, card) && !call_flag)
			{
				call(&CARDS[0], &CARDS[player], player, 1);
				call_flag = 1;
				main_state = ROUND_START;
				
			}
			else
				main_state = SETTLE;

			clearCardset(&cards_to_play);
			
		}
		else if (main_state == SETTLE)
		{
			settle(&game_state, card, &CARDS[player], &CARDS[0]);
			printf("等待结算.\n");
			Sleep(100);

			main_state = ROUND_END;			
		}
		else if (main_state == ROUND_END)
		{
			// 写入日志
			writeToLog(game_state, msgListPtr, CARDS, card);
			call_flag = 0;

			int nplayer = getNextPlayer(game_state);

			Sleep(1000);
			if (CARDS[game_state.player].size == 0)
				main_state = GAME_END;
			else
			{
				game_state.player = nplayer;
				main_state = ROUND_START;
			}	
			Sleep(1000);
		}
		else if (main_state == GAME_END)
		{
			Sleep(1000);
			break;
		}
	}

	WaitForSingleObject(uiThread, INFINITE);
	CloseHandle(uiThread);
	CloseHandle(messageListMutex);

	return 0;
}



STATE init_state()
{
	STATE game_state;

	srand((unsigned int)time(NULL));
	
	game_state.color = rand() % 4 + 1;
	game_state.direction = 1;
	game_state.last_card = NONE;
	game_state.penalty = 0;
	game_state.player = rand() % PLAYER_NUM + 1;
	game_state.plus_four = 0;
	game_state.plus_two = 0;
	game_state.skip = 0;

	return game_state;
}

void init_log()
{
	FILE * fp = fopen("log.txt", "w+");
	fprintf(fp, "Uno Log \n"
				"\n=====================\n");
	fclose(fp);
}

void main_loop()
{
	init_log();

	mainThreadHandle = CreateThread(NULL, 0, mainThread, NULL, 0, NULL);

	WaitForSingleObject(mainThreadHandle, INFINITE);
	CloseHandle(mainThreadHandle);

	delMsg();
}