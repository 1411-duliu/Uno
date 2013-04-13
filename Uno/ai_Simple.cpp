#include <stdio.h>
#include <stdlib.h>

#include "uno.h"

/*简单AI,仅统计当前自己手中的牌，从中推算出最合理出牌方式*/
CARD AI_SIMPLE(CARDSET *cardset,CARDSET *cards)
//cardset给入当前出牌玩家手牌，cards给入当前可出手牌
{
    CARD card={0,0},currentCard;
    int i,j,temp,isFunction=0;
    int count_Function=0,count_Num=0;
    int count_Color[5],array[5]={0,1,2,3,4};

    /*当前若有且仅有一张牌可以出，则打出它*/
    if(cards->size==1)
        return cards->cards[0];

    /*统计当前玩家手牌中的牌种类*/
    for(i=0;i<=cardset->size-1;i++){
        currentCard=cardset->cards[i];
        /*统计手牌中功能牌的比例*/
        if(currentCard.name<=16&&currentCard.name>=12)
            count_Function++;
        else
            count_Num++;

        /*统计手牌中各种颜色牌的比例*/
        count_Color[currentCard.color]++;
    }

    for(i=0;i<=3;i++){   //冒泡排序对四种颜色牌按数量进行递减排序
        for(j=1;j<=3;j++){
            if(count_Color[j]<count_Color[j+1]){
                temp=array[j];         //array数组标号为颜色
                array[j]=array[j+1];   //array数组中存放大小顺序
                array[j+1]=temp;
            }
        }              //处理结果为array数组中存放数字越小，对应颜色拥有数越高
    }

        /*判断当前玩家能打出的手牌是否有功能牌*/
    for(j=0;j<=cards->size-1;j++){
        currentCard=cards->cards[j];
        if(currentCard.name>=12&&currentCard.name<=16)
            isFunction=1;
    }


    /*决定最终出牌的部分*/
    if(isFunction==1&&count_Function>=count_Num){  //有功能牌可出且适合出功能牌时
        for(j=0;j<=cards->size-1;j++){             //筛选最合适的出牌
            currentCard=cards->cards[j];
            if(currentCard.name>=12&&currentCard.name<=16){
                if(currentCard.name==16){
                    if(card.color==0&&card.name==0) //降低+4牌的出牌的优先级
                        card=currentCard;
                }
                else
                    card=currentCard;
            }
        }
    }
    else{  //其它情况只能出数字牌
        for(j=0;j<=cards->size-1;j++){
            currentCard=cards->cards[j];
            if(j==0)
                card=currentCard;
            else{
                if(array[currentCard.color]<card.color)  //选择比重最大的颜色优先进行出牌
                    card=currentCard;
            }
        }
    }

    return card;
}

int chooseColor(CARDSET cardset)
{
	int colorCardNum[5]={0};

	for (int i = 0; i < cardset.size; i++)
		colorCardNum[cardset.cards[i].color] += 1;

	int color = 1;

	for (int i = 0; i < 5; i++)
	{
		if(colorCardNum[i] >  colorCardNum[color])
			color = i;
	}

	return color;
}