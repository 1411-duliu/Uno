#ifndef FUNC_CARD_H
#define FUNC_CARD_H

void skip(STATE *);
void reverse(STATE *);
void plus_two(STATE *);
void plus_four(STATE *);
void wild(STATE *);
void none_card(STATE *,CARDSET *,CARDSET *);
void changeColor(STATE * game_state, int color);
void call(CARDSET * cardset, CARDSET * player_cardset, int player, int n);
void settle(STATE * game_state, CARD card, CARDSET * player_cards, CARDSET * all_cards);

#endif