#include <stdio.h>
#include <stdlib.h>

#include "uno.h"

/*����������Ƿ���������*/
int hasIsCard(CARDSET cards, CARD card){
    int i,IsCard=0;
    CARD currentCard;

    for(i=0;i<=cards.size-1;i++){
        currentCard=cards.cards[i];
        if(card.color==currentCard.color&&card.name==currentCard.name)
            IsCard=1;
    }

    return IsCard;
}

/*���Ʋ��뵽������*/
void insertToCardset(CARDSET * cards, CARD card){
    int currentSize;
    CARD currentCard;
    cards->size++;
    currentSize=cards->size;
    currentCard.color=card.color;
    currentCard.name=card.name;
    cards->cards[currentSize]=currentCard;
}

/*���ƴ�������ɾ��*/
void deleteFromCardset(CARDSET * cards, CARD card){
    int i,j,flag=0;
    CARD currentCard;
    for(i=0;i<=cards->size-1,flag=0;i++){
        currentCard=cards->cards[i];
        if(card.color==currentCard.color&&card.name==currentCard.name){
            flag=1;
            for(j=i;j<=cards->size-2;j++){
                cards->cards[j]=cards->cards[j+1];
                cards->size--;
            }
        }
    }

    cards->size--;
}

/*�������*/
void clearCardset(CARDSET * cards){
    int i;
    CARD emptyCard={0,0};
    for(i=0;i<=cards->size-1;i++){
        cards->cards[i]=emptyCard;
    }

    cards->size=0;
}