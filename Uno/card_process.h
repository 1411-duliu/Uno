#ifndef CARD_PROC_H
#define CARD_PROC_H

CARDSET genCardsToPlay(STATE game_state, CARDSET cards);
CARD genCard(char * input);
void genCardsToPlay(CARDSET * cards_to_play, STATE game_state, CARDSET cards);

#endif
