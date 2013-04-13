#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uno.h"

void writeFile(STATE game_state, CARDSET cards)
{
	FILE *wPtr;
	int i;
	
	wPtr=fopen("File.txt","w");

	fprintf(wPtr,"=== State ===\n");
	fprintf(wPtr,"direction:%d\t",game_state.direction);
	fprintf(wPtr,"player:%d\t",game_state.player);
	fprintf(wPtr,"color:%20d\t",game_state.color);
	fprintf(wPtr,"last_card:%20d\n",game_state.last_card);
	fprintf(wPtr,"plus_2:%d\t",game_state.plus_two);
	fprintf(wPtr,"plus_4:%d\t",game_state.plus_four);
	fprintf(wPtr,"skip:%d\t",game_state.skip);
	fprintf(wPtr,"penalty:%d\t\n\n",game_state.penalty);
		
	for (i=0;i<=cards.size;i++)
	{
		fprintf(wPtr,"player's cards:\n");
		fprintf(wPtr,"-%d-    %d,%d\t",i,cards.cards[i].color,cards.cards[i].name);
		if (i==4||i==9||i==14)
			fprintf(wPtr,"\n");
	}
}