#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uno.h"

char * COLORS[5] = {"NONE", "GREEN", "RED", "YELLOW", "BLUE"};
char * NAMES[17] = {"0","1","2","3","4","5","6","7","8","9","NONE","CALL","REVERSE","SKIP","PLUS2","WILD","PLUS4"};

void printGameState(STATE game_state)
{
	printf("=== GAME_STATE ===\n");
	printf("--> Basic State\n");
	printf("direction: %d\n", game_state.direction);
	printf("color: %s\n", COLORS[game_state.color]);
	printf("card: %s\n", COLORS[game_state.last_card]);
	printf("player: %d\n", game_state.player);
	printf("--> Penalties\n");
	printf("plus_two: %d\n", game_state.plus_two);
	printf("plus_four: %d\n", game_state.plus_four);
	printf("penalty: %d\n", game_state.penalty);
	printf("skip: %d\n", game_state.skip);
	printf("------------------\n");
}

char * cardToStr(CARD card)
{
	char * str;
	int name, color;
	str = (char *)malloc(sizeof(char) * 10);
	color = strlen(COLORS[card.color]);
	name = strlen(NAMES[card.name]);
	strncpy(str, COLORS[card.color], color);
	strncpy(str + color, ",", 1);
	strcpy(str + color + 1, NAMES[card.name]);
	str[color + name + 1] = '\0';

	return str;
}

void printCardset(CARDSET cardset)
{
	for (int j = 0; j < cardset.size; j++)
			printf("- %d - %s\n", j, cardToStr(cardset.cards[j]));
}

void printEntityCards(CARDSET CARDS[])
{
	for (int i = 0; i <= 4; i++)
	{
		printf("--> PLAYER %d --> %d cards \n", i, CARDS[i].size);
		printCardset(CARDS[i]);
	}
}