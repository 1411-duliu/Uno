#include <stdio.h>
#include <stdlib.h>
#include "uno.h"

/*检查这张牌是否在牌组中*/
int hasThisCard(CARDSET cards, CARD card){
    int i,IsCard=0;
    CARD currentCard;

    for(i=0;i<=cards.size-1;i++){
        currentCard=cards.cards[i];
        if(card.color==currentCard.color&&card.name==currentCard.name)
            IsCard=1;
    }

    return IsCard;
}

/*将牌插入到牌组中*/
void insertToCardset(CARDSET * cards, CARD card){
    int currentSize;
    CARD currentCard;
    cards->size++;
    currentSize=cards->size;
    currentCard.color=card.color;
    currentCard.name=card.name;
    cards->cards[currentSize - 1]=currentCard;
}

/*将牌从牌组中删除*/
void deleteFromCardset(CARDSET * cards, CARD card){
    int i,j;
    CARD currentCard;
	
    for(i=0; i<=cards->size-1; i++){
        currentCard=cards->cards[i];
		// printf("To delete: color %d, name %d.\n Now: color %d, name %d.\n", card.color, card.name, currentCard.color, currentCard.name);
        if(card.color==currentCard.color&&card.name==currentCard.name){ 
            for(j=i;j<=cards->size-2;j++){
                cards->cards[j]=cards->cards[j+1];
            }

			cards->size--;
			return;
        }
    }
}

/*清空牌组*/
void clearCardset(CARDSET * cards){
    int i;
    CARD emptyCard={0,0};
    for(i=0;i<=cards->size-1;i++){
        cards->cards[i]=emptyCard;
    }

    cards->size=0;
}