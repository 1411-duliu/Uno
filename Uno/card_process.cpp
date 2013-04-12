#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uno.h"
#include "cardset_process.h"
#include "utilities.h"

char  *stdcolor[]={"NONE","GREEN","RED","YELLOW","BLUE"};
char  *stdface[]={"0","1","2","3","4","5","6","7","8","9","NONE","CALL","REVERSE","SKIP","PLUS2","WILD","PLUS4"};

int isNormalCard(CARD card) //�ж��Ƿ�����ͨ��
{
	if (card.name<=9&&card.name>=0)
		return 1;
	return 0;
}


int isFuncCard(CARD card) //�ж��Ƿ��ǹ�����
{
	if (card.name<=14&&card.name>=12)
		return 1;
	return 0;
}


int isWildCard(CARD card) //�ж��Ƿ���������
{
	if (card.name>14)
		return 1;
	return 0;
}

int isValid(CARD card)
{
	return !(card.color == CNONE && card.name == INVALID);
}

void genCardsToPlay(CARDSET * cards_to_play, STATE game_state, CARDSET cards)  //�õ���ǰ���Գ�����
{
	int i=0, j=1;
	
	clearCardset(cards_to_play);   // ��ʼ��������
	CARD none, call;

	none.color=0;					//��none����NONE
	none.name=10;
	call.color=0;					//��call����CALL
	call.name=11;


	if (game_state.skip==0)         //�ж��Ƿ�����
	{
		if (game_state.plus_two==1) //�ж��Ƿ�+2
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==14)						 //����+2 
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //����ɳ��ƶ� 
				}
				else if (cards.cards[j].name==16)				   	 //����+4
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //����ɳ��ƶ�
				}
			}
			insertToCardset(cards_to_play,none);          //NONE����ɳ��ƶ�
		}
		else if (game_state.plus_four==1)  //�ж��Ƿ�+4
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==16)  //����+4
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //����ɳ��ƶ�
				}
			}
			insertToCardset(cards_to_play,none);          //NONE����ɳ��ƶ�
		}
		else  //��ͨ��
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].color==game_state.color || cards.cards[j].color == CNONE)  //�ж���ɫ
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //����ɳ��ƶ�
				}
				else if (cards.cards[j].name==game_state.last_card)     //�ж�����
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //����ɳ��ƶ�
				}
			}
			
			insertToCardset(cards_to_play,call);					//CALL����ɳ�����
		}
	}
	else
		insertToCardset(cards_to_play,none);          //NONE����ɳ��ƶ�

}

CARD genCard(char * input)
{
	CARD card;

	int n;
    char content[20];
    char color[10];
    char face[10];
    char *r=",",*Ptr,c=',';

	int flag = 0;

	if((Ptr=strchr(input,c))!=NULL)
	{   
		//�ж�������ַ������Ƿ���ڶ��ţ�������ڽ���ַ����Ptr
        n=strcspn(input,r);  //�ж϶����������еڼ������������α���n
        strncpy(color,input,n); //��content���鿪ʼ����nΪ��color�У���Ϊ�������ɫ
        color[n]='\0';
        strcpy(face,(Ptr+1));                //��Ptr��ַ��ʼ�����µ��ַ������Ƶ�face�����У���Ϊ�������ֵ
        
		for (int i = 0; i < 5; i++)
		{
			if (strcmp(color, stdcolor[i]) == 0)
			{
				card.color = i;
				flag = 1;
				
				break;
			}
			
		}
		for (int i = 0; i < 17; i++)
			if (strcmp(face, stdface[i]) == 0)
			{
				card.name = i;
				flag += 1;
			}
	}


	if(flag != 2)
	{
		card.color=0;
		card.name=1411;
	}
	

	return card;
}