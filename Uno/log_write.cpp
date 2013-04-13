#include <stdio.h>
#include <stdlib.h>

#include "uno.h"
#include "utilities.h"

extern char * COLORS[];
extern char * NAMES[];

FILE * logFp;

void writeGameState(STATE game_state)
{
	fprintf(logFp,"\n=== GAME_STATE ===\n");
	fprintf(logFp,"--> Basic State\n");
	fprintf(logFp,"direction: %d\t", game_state.direction);
	fprintf(logFp,"color: %s\t", COLORS[game_state.color]);
	fprintf(logFp,"card: %s\t", NAMES[game_state.last_card]);
	fprintf(logFp,"player: %d\n", game_state.player);
	fprintf(logFp,"--> Penalties\n");
	fprintf(logFp,"plus_two: %d\t", game_state.plus_two);
	fprintf(logFp,"plus_four: %d\t", game_state.plus_four);
	fprintf(logFp,"penalty: %d\t", game_state.penalty);
	fprintf(logFp,"skip: %d\n", game_state.skip);
	fprintf(logFp,"------------------\n");
}

void writeCardset(CARDSET cardset)
{
	for (int j = 0; j < cardset.size; j++)
	{
		fprintf(logFp, "- %d - %15s | ", j, cardToStr(cardset.cards[j]));
		if (!((j + 1) % 3)) fprintf(logFp, "\n");
	}
	fprintf(logFp, "\n");
}

void writeEntityCards(CARDSET CARDS[])
{
	for (int i = 1; i <= PLAYER_NUM; i++)
	{
		fprintf(logFp, "--> PLAYER %d --> %d cards \n", i, CARDS[i].size);
		writeCardset(CARDS[i]);
	}
}

void writeMsg(FILE * fp, MSGLISTNODEPTR msgListPtr)
{
	MSGLISTNODEPTR currentPtr = msgListPtr, tmp;
	
	int count = 0;

	fprintf(fp, "消息列表:\n");
	while (currentPtr != NULL && count < MAX_MSG_NUM)
	{
		fprintf(fp, "Msg: %s\n", currentPtr->msg);
		currentPtr = currentPtr->nextPtr;
		count++;
	}
	fprintf(fp, "----------------\n");
}

void writeToLog(STATE game_state, MSGLISTNODEPTR msgListPtr, CARDSET CARDS[], CARD card)
{

	logFp = fopen("log.txt", "a");

	fprintf(logFp, "\n");

	writeMsg(logFp, msgListPtr);
	writeGameState(game_state);
	writeEntityCards(CARDS);

	fprintf(logFp, "%s\n", playCardMsg(game_state.player, card));

	fprintf(logFp, "回合结束. \n\n");

	
	fclose(logFp);
}

