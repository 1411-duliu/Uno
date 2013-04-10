#include <stdio.h>
#include <stdlib.h>
#include "uno.h"
#include "cardset_process.h"


int isNormalCard(CARD card)  //�ж��Ƿ�����ͨ��
{
	if (card.name<=9&&card.name>=0)
		return 1;
	return 0;
}


int isFuncCard(CARD card)    //�ж��Ƿ��ǹ�����
{
	if (card.name<=14&&card.name>=12)
		return 1;
	return 0;
}


int isWildCard(CARD card)    //�ж��Ƿ���������
{
	if (card.name>14)
		return 1;
	return 0;
}


CARDSET genCardsToPlay(STATE game_state, CARDSET cards)  //�õ���ǰ���Գ�����
{
	CARDSET cards_to_play;
	clearCardset(&cards_to_play); // ��ʼ��������
	int i=0, j=1;

	if (game_state.skip==0) //�ж��Ƿ�����
	{
		if (game_state.plus_two==1)  //�ж��Ƿ�+2
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==14)  //����+2 
				{
					cards_to_play.cards[i]=cards.cards[j];  //����ɳ��ƶ� 
					i++;
				}
				else if (cards.cards[j].name==16)  //����+4
				{
					cards_to_play.cards[i]=cards.cards[j];  //����ɳ��ƶ�
					i++;
				}
			}
			
			//NONE����ɳ��ƶ�
			cards_to_play.cards[i].color=0;
			cards_to_play.cards[i].name=10;
			i++;
		}
		else if (game_state.plus_four==1)  //�ж��Ƿ�+4
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==16)  //����+4
				{
					cards_to_play.cards[i]=cards.cards[j];  //����ɳ��ƶ�
					i++;
				}
			}
			//NONE����ɳ��ƶ�
			cards_to_play.cards[i].color=0;
			cards_to_play.cards[i].name=10;
			i++;
		}
		else  //��ͨ��
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].color==game_state.color)  //�ж���ɫ
				{
					cards_to_play.cards[i]=cards.cards[j];
					i++;
				}
				else if (cards.cards[j].name==game_state.last_card)     //�ж�����
				{
					if (hasThisCard(cards_to_play,cards.cards[j])==0)   //��ɫ�������Ƿ����ظ�
					{
						cards_to_play.cards[i]=cards.cards[j];
						i++;
					}
				}
			}
			//NONE����ɳ��ƶ�
			cards_to_play.cards[i].color=0;
			cards_to_play.cards[i].name=11;
			i++;
		}
	}
	else  //NONE����ɳ��ƶ�
	{
		cards_to_play.cards[i].color=0;
		cards_to_play.cards[i].name=10;
		i++;
	}

	cards_to_play.size = i;

	return cards_to_play;
}