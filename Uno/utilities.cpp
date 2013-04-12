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
	printf("direction: %d\t", game_state.direction);
	printf("color: %s\t", COLORS[game_state.color]);
	printf("card: %s\t\t", NAMES[game_state.last_card]);
	printf("player: %d\n", game_state.player);
	printf("--> Penalties\n");
	printf("plus_two: %d\t", game_state.plus_two);
	printf("plus_four: %d\t", game_state.plus_four);
	printf("penalty: %d\t", game_state.penalty);
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
	{
		printf("- %d - %15s | ", j, cardToStr(cardset.cards[j]));
		if (!((j + 1) % 3)) printf("\n");
	}
	printf("\n");
}

void printEntityCards(CARDSET CARDS[])
{
	for (int i = 0; i <= 4; i++)
	{
		printf("--> PLAYER %d --> %d cards \n", i, CARDS[i].size);
		printCardset(CARDS[i]);
	}
}

char * playCardMsg(int player, CARD card)
{
	char * msg = (char *)malloc(sizeof(char)*50);
	strcpy(msg, "玩家");
	
	int len = strlen(msg);
	
	msg[len] = player + '0';
	strcpy(msg + len + 1, " 打出了 ");
	len = strlen(msg);
	strcpy(msg + len, cardToStr(card));

	return msg;
}

int strToColor(char * str)
{
	for (int i = 0; i <= 4; i++)
	{
		if (strcmp(COLORS[i], str) == 1)
			return i;
	}

	return -1;
}