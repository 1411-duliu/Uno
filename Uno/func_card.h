#ifndef FUNC_CARD_H
#define FUNC_CARD_H

void skip(STATE *);
void reverse(STATE *);
void plus_two(STATE *);
void plus_four(STATE *);
void wild(STATE *);
void none_card(STATE *,CARDSET *,CARDSET *);
void changeColor(STATE * game_state, int color);

#endif