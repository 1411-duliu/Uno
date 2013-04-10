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

int main_state;

void init_state()
{
	srand((unsigned int)time(NULL));
	
	game_state.color = rand() % 4 + 1;
	game_state.direction = rand() % 2;
	game_state.last_card = NONE;
	game_state.penalty = 0;
	game_state.player = rand() % PLAYER_NUM + 1;
	game_state.plus_four = 0;
	game_state.plus_two = 0;
	game_state.skip = 0;
}

void init_game()
{
	CARD * cards = generateCards();
    shuffleCards(cards);
	getIntoCardset(&CARDS[0], cards, 108);
	distributeCards(CARDS, CARDS[0], PLAYER_NUM);

	init_state();
}

int main(int argc, const char * argv[])
{
	init_game();
	// printGameState(game_state);

	STATE test_state = {1, 1, GREEN, PLUS_2, 1, 0, 0, 0};
	CARDSET test_cardset, iCardset;
	CARD cards[2] = {{GREEN,1}, {RED, PLUS_4}};
	getIntoCardset(&test_cardset, cards, 2);
	iCardset = genCardsToPlay(test_state, test_cardset);
	printCardset(iCardset);

	system("pause");

    return 0;
}
