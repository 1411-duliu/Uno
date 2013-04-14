#include <stdio.h>
#include <stdlib.h>

#include "uno.h"
#include "game_main.h"
#include "ai_Simple.h"

/*较复杂的AI，统计自己和当前场上局面，
推算出降低他人胜利度的同时，最利于自己的方案*/
CARD AI_HARD(CARDSET *cardset,CARDSET *cards,STATE state,CARDSET player_Card[5])
/*cardset给入当前出牌玩家手牌，cards给入当前可出手牌，state给入当前游戏的运行状态，
player_Card[5]给入所有玩家手牌（本函数只调用所有玩家手牌张数，不分析其他玩家具体手牌）*/
{
	CARD card;


	return card;
}


