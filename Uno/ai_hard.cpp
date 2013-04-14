#include <stdio.h>
#include <stdlib.h>

#include "uno.h"
#include "game_main.h"
#include "ai_Simple.h"

/*较复杂的AI，统计自己和当前场上局面，
推算出降低他人胜利度的同时，最利于自己的方案*/
CARD AI_HARD(CARDSET *cardset,CARDSET *cards,STATE state,
			 CARDSET player_Card[5],CARDSET trash[5])
/*cardset给入当前出牌玩家手牌，cards给入当前可出手牌，state给入当前游戏的运行状态，
player_Card[5]给入所有玩家手牌（本函数只调用所有玩家手牌张数，不分析其他玩家具体手牌）*/
{
	CARD card;
	CARDSET current_Player_Card;
	int i,flag_of_uno;

	for(i=1;i<=4;i++){     //判断场上是否有已经UNO的玩家
		current_Player_Card=player_Card[i];
		if(current_Player_Card==1)
			flag==1;
	}

	if(flag==1)
		card=Project1(cardset,cards,state,player_Card[5],trash[5]);
	else
		card=Project2(cardset,cards,state,player_Card[5],trash[5]);

	return card;
}


/*方案1：针对已有玩家UNO进行反应，给入变量同上*/
CARD Project1(CARDSET *cardset,CARDSET *cards,STATE state,
			 CARDSET player_Card[5],CARDSET trash[5])
{
	CARD card={0,11};
	int i,uno_Player,ifReverse=0;
	int nextPlayer=getNextPlayer(state);  //寻找下一位玩家
	int previousPlayer=getPreviousPlayer(state); //寻找上一位玩家

	CARDSET playerCard;
	playerCard=player_Card[nextPlayer];   

	if(playerCard.size==1){ //下家已UNO时,对下家进行惨无人道的攻击
		for(i=0;i<=cards->size-1;i++){  //从可出的牌中寻找威胁性最大的出牌方案
			currentCard=cards->cards[i];
			if(currentCard.name==16)   //+4最优
				card=currentCard;
			else if(currentCard.name==14&&card.name!=16)
				card=currentCard;     //+2优先度次之
			else if(currentCard.name==13&&card.name!=16&&card.name!=14)
				card=currentCard;     //禁手再次之
		}
		 
		if(card==(0,11)){    //在没有上述功能牌的情况下进行进一步探索
			for(i=0;i<=cards->size-1;i++){  //寻找是否有转向牌
				currentCard=cards->cards[i];
				if(currentCard.name==12)
					ifReverse=1;
			}
			if(ifReverse==1&&previousPlayer.size!=1)
				card={0,12};  //在保证上一玩家未UNO且自己有转向，打出之
			else{
				card=Analyze(trash[nextPlayer],trash[0],cards,state);
			}
		}
	}

	else{ //下家未UNO,而是其他玩家UNO，则寻找UNO目标的最近出牌，
		 //采取与之不同的牌色进行远程压制，此时不出功能牌以免渔翁得利
		
		for(i=2;i<=4;i++){     //锁定到已经UNO的玩家
			current_Player_Card=player_Card[i];	
			if(current_Player_Card.size==1)
				uno_Player=i;
		}
		card=Analyze(trash[uno_Player],trash[0],cards,state);//针对其进行远程打击
	}

	return card;
}


/*方案2：在无人UNO情况下，进行输出，变量同上*/
CARD Project2(CARDSET *cardset,CARDSET *cards,STATE state,
			 CARDSET player_Card[5],CARDSET trash[5])
{
	CARD card={0,11};
	int i;
	int nextPlayer=getNextPlayer(state);  //寻找下一位玩家
	CARDSET playerCard;
	playerCard=player_Card[nextPlayer];   

	if(playerCard.size<=3)
	/*当下家手牌<=3时，对出牌方案进行选择，
	  在考虑自身手牌同时，给予下家适当压力
	  此时不用+4对其进行人道毁灭*/
	{  
		for(i=0;i<=cards->size-1;i++){  //从可出的牌中寻找威胁性最大的出牌方案
			currentCard=cards->cards[i];
			if(currentCard.name==14)   //+2最优
				card=currentCard;
			else if(currentCard.name==13&&card.name!=14)
				card=currentCard;     //禁手优先度次之

			if(card=={0,11}){
				card=Analyze(trash[nextPlayer],trash[0],cards,state)；
				if(card==0,11) //若没有最合适的牌导致自己可能叫牌
					card=ai_Simple(cardset,cards);
				               //则按对自己有利的出牌，没必要玩命
			}
	}

	else  //对于下家仍有较多手牌时，按照简单思路处理，仅考虑自身手牌
		card=ai_Simple(cardset,cards);

	return card;
}

//----------------------------------------------------------------------


/*工具函数部分*/
int getPreviousPlayer(STATE game_state)  
{               //当前玩家的寻找前一个玩家
	int nplayer = game_state.player;

	if (game_state.direction == 1)
	{
		if (nplayer == 1)
			nplayer = PLAYER_NUM;
		else
			nplayer -= 1;
	}
	else
	{
		if (nplayer == PLAYER_NUM)
			nplayer = 1;
		else
			nplayer += 1;
	}

	return nplayer;
}

CARD Analyze(CARDSET playerTrash, CARDSET totalTrash,CARDSET * cards,STATE state)
//传入目标玩家的弃牌堆trash，所有玩家弃牌堆， 当前可以出的牌
//在只能出普通牌和变色牌时，通过分析弃牌堆得出对其压制较强的牌面花色
//此函数最后得出的可能是CALL牌
{
	int i,bestColor,size,voidColor;
	CARD last_Card;//获得目标玩家最近打出的牌
	CARD card={0,11};
	int * colors;

	size=playerTrash.size;
	last_Card=playerTrash.cards[size-1];
	voidColor=last_Card.color;

	for(i=0;i<=cards->size-1;i++){ 
		currentCard=cards->cards[i];
		if(currentCard.name==WILD)  //当拥有变色牌时优先出
			card={bestColor,WILD};    //返回带有当前最适颜色的变色牌
		else if(currentCard.name!=WILD&&currentCard.color!=voidColor){
			if(colors[currentCard.color-1]<colors[card.color-1])
				card=currentCard;
		}

	}

	free(colors);
	return card;
}

int * countColor(CARDSET trash)
//本函数用于统计当前弃牌堆中各色牌的比例
{
	int i,j,temp;
	CARD currentCard;
	int colorCount[5]={0};
	int * colorRank=(int*)malloc(sizeof(int)*5);
	for(i=0;i<=4;i++)
		colorRank(i)=i;

	for(i=0;i<=trash.size-1;i++)
	{
		currentCard=trash.cards[i];
		switch(currentCard.color){
			case 1:
				colorCount[1]++;break;
			case 2:
				colorCount[2]++;break;
			case 3:
				colorCount[3]++;break;
			case 4:
				colorCount[4]++;break;
		}
	}

	for(i=1;i<=4;i++){   //冒泡排序排定各花色的大小顺序
		for(j=1;j<=3;j++){
			if(colorCount[j]<colorCount[j+1]){
				temp=colorRank[j];
				colorRank[j]=colorRank[j+1];
				colorRank[j+1]=temp;
			}       //colorRank中存放的是各花色的排列顺序
		}           //排名越大  对应牌数越多
	}
	return colorRank;
}