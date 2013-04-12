#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uno.h"
#include "cardset_process.h"
#include "utilities.h"

char  *stdcolor[]={"NONE","GREEN","RED","YELLOW","BLUE"};
char  *stdface[]={"0","1","2","3","4","5","6","7","8","9","NONE","CALL","REVERSE","SKIP","PLUS2","WILD","PLUS4"};

int isNormalCard(CARD card) //判断是否是普通牌
{
	if (card.name<=9&&card.name>=0)
		return 1;
	return 0;
}


int isFuncCard(CARD card) //判断是否是功能牌
{
	if (card.name<=14&&card.name>=12)
		return 1;
	return 0;
}


int isWildCard(CARD card) //判断是否是万能牌
{
	if (card.name>14)
		return 1;
	return 0;
}

int isValid(CARD card)
{
	return !(card.color == CNONE && card.name == INVALID);
}

void genCardsToPlay(CARDSET * cards_to_play, STATE game_state, CARDSET cards)  //得到当前可以出的牌
{
	int i=0, j=1;
	
	clearCardset(cards_to_play);   // 初始化新牌组
	CARD none, call;

	none.color=0;					//用none代替NONE
	none.name=10;
	call.color=0;					//用call代替CALL
	call.name=11;


	if (game_state.skip==0)         //判断是否跳过
	{
		if (game_state.plus_two==1) //判断是否+2
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==14)						 //有无+2 
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //加入可出牌堆 
				}
				else if (cards.cards[j].name==16)				   	 //有无+4
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //加入可出牌堆
				}
			}
			insertToCardset(cards_to_play,none);          //NONE加入可出牌堆
		}
		else if (game_state.plus_four==1)  //判断是否+4
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].name==16)  //有无+4
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //加入可出牌堆
				}
			}
			insertToCardset(cards_to_play,none);          //NONE加入可出牌堆
		}
		else  //普通牌
		{
			for (j=0;j<cards.size;j++)
			{
				if (cards.cards[j].color==game_state.color || cards.cards[j].color == CNONE)  //判断颜色
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //加入可出牌堆
				}
				else if (cards.cards[j].name==game_state.last_card)     //判断数字
				{
					insertToCardset(cards_to_play,cards.cards[j]);  //加入可出牌堆
				}
			}
			
			insertToCardset(cards_to_play,call);					//CALL加入可出牌组
		}
	}
	else
		insertToCardset(cards_to_play,none);          //NONE加入可出牌堆

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
		//判断输入的字符串中是否存在逗号，如果存在将地址赋给Ptr
        n=strcspn(input,r);  //判断逗号是数组中第几个，赋给整形变量n
        strncpy(color,input,n); //从content数组开始复制n为到color中，即为输入的颜色
        color[n]='\0';
        strcpy(face,(Ptr+1));                //从Ptr地址开始将余下的字符串复制到face数组中，即为输入的面值
        
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