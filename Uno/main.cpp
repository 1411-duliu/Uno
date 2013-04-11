#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "uno.h"
#include "generate_card.h"
#include "cardset_process.h"
#include "card_process.h"
#include "utilities.h"

CARDSET CARDS[5];
STATE game_state;

int main_state = 1;

CARD NONE_CARD = {CNONE, NONE};
CARD INVALID_CARD = {CNONE, INVALID};
CARD CALL_CARD = {CNONE, CALL};

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

void init_game()
{
	CARD * cards = generateCards();
    shuffleCards(cards);
	getIntoCardset(&CARDS[0], cards, 108);
	distributeCards(CARDS, CARDS[0], PLAYER_NUM);

	game_state = init_state();
}

int main(int argc, const char * argv[])
{
	init_game();
	// printGameState(game_state);
	int player;
	CARDSET cards_to_play;

	while (main_state != GAME_END)
	{
		player = game_state.player;
		
		if (main_state == ROUND_START)
		{
			cards_to_play = genCardsToPlay(game_state, CARDS[player]);
			printCardset(cards_to_play);
			if (hasThisCard(cards_to_play, NONE_CARD) && cards_to_play.size == 1)
			{
				// 如果可出的牌中只有1张NONE，那么不能出牌
				printf("本局不能出牌，进入结算阶段。");
				Sleep(2000);
				main_state = SETTLE; // 进入结算状态
				continue;
			}
			main_state = PLAY_CARD;
		}
		else if (main_state == PLAY_CARD)
		{
			CARD card;
			
			while (!(isValid(card = genCard(getInput())) && hasThisCard(cards_to_play, card)))
			{
				system("cls");
				printf("输入不合法，请重新输入。\n");
				printCardset(cards_to_play);
			}
			
			printf("\nInput: %s\n", cardToStr(card));

			break;
		}
	}

	system("pause");

    return 0;
}
