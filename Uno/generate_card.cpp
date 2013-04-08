#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "uno.h"


CARD * generateCards() 
{
    CARD* cards;
    cards = (CARD *) malloc(sizeof(CARD) * 108);
    
    int color;
    int i;
    int count = 0, color_cards = 0;
    
    for (color = 1; color <= 4; color++) {
        cards[count].color = color;
        cards[count].name = 0;
        color_cards = 1;
        count++;
        while (color_cards <= 9) {
            cards[count].color = color;
            cards[count].name = color_cards;
            count++;
            cards[count].color = color;
            cards[count].name = color_cards;
            count++;
            color_cards++;
        }
        
    }
    
    count = 4 * 19;
    
    for (color = 1; color <= 4; color++) {
        for (i = 0; i < 2; i++) {
            cards[count].color = color;
            cards[count++].name = REVERSE;
            cards[count].color = color;
            cards[count++].name = PLUS_2;
            cards[count].color = color;
            cards[count++].name = SKIP;
        }
    }
    
    
    for (i = 0; i < 4 ; i++) {
        cards[count].color = 0;
        cards[count++].name = PLUS_4;
        
        cards[count].color = 0;
        cards[count++].name = WILD;
    }
    
    return cards;
}

void shuffleCards(CARD * cards)
{
    CARD swp_card;
    srand((unsigned int)time(NULL));
    
    int i;
    int r1, r2;
    for (i = 0; i <= 1000; i++) {
        r1 = (int)rand()%108;
        r2 = (int)rand()%108;
        swp_card = cards[r1];
        cards[r1] = cards[r2];
        cards[r2] = swp_card;
    }
    
}

void getIntoCardset(CARDSET * cardset, CARD * cards, int size)
{
    cardset->size = size;
    int i;
    for (i = 0; i<=size-1; i++) {
        cardset->cards[i] = cards[i];
    }
}
