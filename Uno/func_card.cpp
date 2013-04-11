#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uno"

char  *stdcolor[]={"CNONE","GREEN","RED","YELLOW","BLUE"};

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
        game_state->plus_2=1;
        game_state->penalty+=2;
}



void plus_four(STATE *game_state)
{
        char chancol[];
	
		game_state->plus_4=1;
        game_state->plus_2=0;
        game_state->penalty+=4;

		scanf("%s",chanclo);
        if((strcmp(chanclo,*(stdcolor+1)))==1)
        {
            game_state->color=1;
        }
        else if((strcmp(chanclo,*(stdcolor+2)))==1)
        {
            game_state->color=2;
        }
        else if((strcmp(chanclo,*(stdcolor+3)))==1)
        {
            game_state->color=3;
        }
        else if((strcmp(chanclo,*(stdcolor+4)))==1)
        {
            game_state->color=4;
        }
}


void wild(STATE *game_state)
{
        char chancol[];
        scanf("%s",chanclo);
        if((strcmp(chanclo,*(stdcolor+1)))==1)
        {
            game_state->color=1;
        }
        else if((strcmp(chanclo,*(stdcolor+2)))==1)
        {
            game_state->color=2;
        }
        else if((strcmp(chanclo,*(stdcolor+3)))==1)
        {
            game_state->color=3;
        }
        else if((strcmp(chanclo,*(stdcolor+4)))==1)
        {
            game_state->color=4;
        }
}

void none_card(STATE *game_state,CARDSET *cardset,CARDSET *player)
{
            int n,i,k,g;
            n=game_state->penalty;
            g=player->size;
            for(i=1;i<=n;i++)
            {
                k=cardset->size;
                player->cards[g+i]->color=cardset->card[k]->color;
                player->cards[g+i]->name=cardset->card[k]->name;
                cardset->cards[k]={0,0};
                cardset->size--;
            }
}
