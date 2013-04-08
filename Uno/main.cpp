#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "uno.h"
#include "generate_card.h"

void init_game();
void init_state();

CARDSET CARDS[5];

STATE game_state;
int main_state;



int main(int argc, const char * argv[])
{
	init_game();
	system("pause");

    return 0;
}

void init_game()
{
	 CARD * cards;
    
	cards = generateCards();
    shuffleCards(cards);
	getIntoCardset(&CARDS[0], cards, 108);
	// CARDS[0].cards = cards;

	for (int i = 1; i<=4; i++) {
        getIntoCardset(&CARDS[i], cards + (107-7*i), 7);
		CARDS[i].size = 7;
		CARDS[0].size -= 7;
    }

    for (int i = 1; i < 5; i++) {
		for	(int j = 0; j < 7 ; j++)
		{
			printf("USER = %d ID = %d COLOR %d NAME %d \n",i , j , CARDS[i].cards[j].color, CARDS[i].cards[j].name);
    
		}
	}
}

void init_state()
{
	srand((unsigned int)time(NULL));

	game_state.color = rand() % 4 + 1;
	game_state.direction = rand() % 2;
	game_state.last_card = 0;
	game_state.player = rand();
}