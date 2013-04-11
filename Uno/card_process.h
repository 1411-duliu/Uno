#ifndef CARD_PROC_H
#define CARD_PROC_H

void genCardsToPlay(CARDSET * cards_to_play, STATE game_state, CARDSET cards);
CARD genCard(char * input);
int isValid(CARD card);
int isFuncCard(CARD card);
int isNormalCard(CARD card);
int isWildCard(CARD card);
int isValid(CARD card);

#endif
