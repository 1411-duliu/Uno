#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uno.h"
#include "utilities.h"
#include "card_process.h"
#include "user_input.h"
#include "cardset_process.h"
#include "user_interface.h"

int color;

void changeColor(STATE * game_state, int color)
{
	game_state->color = color;
}


void skip(STATE *game_state)
{
	game_state->skip=1;
}


void reverse(STATE *game_state)
{
	switch(game_state->direction)
	{
		case 0:
			game_state->direction=1;
			break;
		case 1:
			game_state->direction=0;
			break;
	}
}

void plus_two(STATE *game_state)
{
	game_state->plus_two=1;
	game_state->penalty+=2;
}

void plus_four(STATE * game_state)
{
	char chanclo[10];

	game_state->plus_four=1;
	game_state->plus_two=0;
    game_state->penalty+=4;

	while ((color = getColor()) <= 0);

	changeColor(game_state, color);

}

void wild(STATE *game_state)
{
	char chanclo[10];

	while ((color = getColor()) <= 0);
	changeColor(game_state, color);
}

void call(CARDSET * cardset, CARDSET * player_cardset, int player, int n)
{
    for(int i = 1; i <= n; i++)
    {
		insertToCardset(player_cardset, cardset->cards[cardset->size - 1]);
		cardset->size--;
	}

	char msg[30];
	strcpy(msg, "Íæ¼Ò");
	int length = strlen(msg);
	itoa(player, msg+length, 10);
	strcat(msg, " ½ÐÅÆ ");
	length = strlen(msg);
	itoa(n, msg+length, 10);
	strcat(msg, " ÕÅ.");
	addMsg(msg);
}

void none_card(STATE *game_state,CARDSET *cardset,CARDSET *player)
{
	call(cardset, player, game_state->player ,game_state->penalty);

	game_state->plus_two = 0;
	game_state->penalty = 0;
	game_state->plus_four = 0;
	game_state->skip = 0;
}

void settle(STATE * game_state, CARD card, CARDSET * player_cards, CARDSET * all_cards)
{
	if (!(card.name == CALL || card.name == NONE))
		deleteFromCardset(player_cards, card);

	if (isWildCard(card))
	{
		if (card.name == PLUS_4) plus_four(game_state);
		if (card.name == WILD) wild(game_state);
	}

	if (isFuncCard(card) || isNormalCard(card))
	{
		if (card.name == REVERSE) reverse(game_state);
		if (card.name == PLUS_2) plus_two(game_state);
		if (card.name == SKIP) skip(game_state);

		game_state->color = card.color;
		game_state->last_card = card.name;
	}

	if (card.name == CALL) call(all_cards, player_cards, game_state->player, 1);
	if (card.name == NONE) none_card(game_state, all_cards, player_cards);

}

