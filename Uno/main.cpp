#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "uno.h"
#include "generate_card.h"

CARDSET CARDS[5];

int main(int argc, const char * argv[])
{
    CARD * cards;
    
	cards = generateCards();
    shuffleCards(cards);
	getIntoCardset(&CARDS[0], cards, 108);
	// CARDS[0].cards = cards;

	for (int i = 1; i<=4; i++) {
        getIntoCardset(&CARDS[i], cards + (107-7*i), 7);
		CARDS[0].size -= 7;
    }

    for (int i = 1; i < 5; i++) {
		for	(int j = 0; j < 7 ; j++)
		{
			printf("USER = %d ID = %d COLOR %d NAME %d \n",i , j , CARDS[i].cards[j].color, CARDS[i].cards[j].name);
    
		}
	}
    
	system("pause");

    return 0;
}

