#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "uno.h"
#include "generate_card.h"


int main(int argc, const char * argv[])
{
    CARD * cards;
    
    cards = generateCards();
    shuffleCards(cards);
    int i;
    for (i = 0; i < 108; i++) {
        printf("%d COLOR %d NAME %d \n",i , cards[i].color, cards[i].name);
    }
    
	Sleep(1000);

    return 0;
}

