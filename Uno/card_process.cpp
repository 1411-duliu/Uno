#include <stdio.h>
#include <stdlib.h>
#include "uno.h"
#include "cardset_process.h"


int isNormalCard(CARD card)  //判断是否是普通牌
{
	if (card.name<=9&&card.name>=0)
		return 1;
	return 0;
}


int isFuncCard(CARD card)    //判断是否是功能牌
{
	if (card.name<=14&&card.name>=12)
		return 1;
	return 0;
}


int isWildCard(CARD card)    //判断是否是万能牌
{
	if (card.name>14)
		return 1;
	return 0;
}


CARDSET genCardsToPlay(STATE game_state, CARDSET cards)  //得到当前可以出的牌
{
	CARDSET cards_to_play;
	clearCardset(&cards_to_play); // 初始化新牌组
	int i=0, j=1;

	if (game_state.skip==0) //判断是否跳过
	{
		if (game_state.plus_two==1)  //判断是否+2
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==14)  //有无+2 
				{
					cards_to_play.cards[i]=cards.cards[j];  //加入可出牌堆 
					i++;
				}
				else if (cards.cards[j].name==16)  //有无+4
				{
					cards_to_play.cards[i]=cards.cards[j];  //加入可出牌堆
					i++;
				}
			}
			
			//NONE加入可出牌堆
			cards_to_play.cards[i].color=0;
			cards_to_play.cards[i].name=10;
			i++;
		}
		else if (game_state.plus_four==1)  //判断是否+4
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==16)  //有无+4
				{
					cards_to_play.cards[i]=cards.cards[j];  //加入可出牌堆
					i++;
				}
			}
			//NONE加入可出牌堆
			cards_to_play.cards[i].color=0;
			cards_to_play.cards[i].name=10;
			i++;
		}
		else  //普通牌
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].color==game_state.color)  //判断颜色
				{
					cards_to_play.cards[i]=cards.cards[j];
					i++;
				}
				else if (cards.cards[j].name==game_state.last_card)     //判断数字
				{
					if (hasThisCard(cards_to_play,cards.cards[j])==0)   //颜色，数字是否有重复
					{
						cards_to_play.cards[i]=cards.cards[j];
						i++;
					}
				}
			}
			//NONE加入可出牌堆
			cards_to_play.cards[i].color=0;
			cards_to_play.cards[i].name=11;
			i++;
		}
	}
	else  //NONE加入可出牌堆
	{
		cards_to_play.cards[i].color=0;
		cards_to_play.cards[i].name=10;
		i++;
	}

	cards_to_play.size = i;

	return cards_to_play;
}