#include <stdio.h>
#include <stdlib.h>

#include "uno.h"

/*��AI,��ͳ�Ƶ�ǰ�Լ����е��ƣ�����������������Ʒ�ʽ*/
CARD AI_SIMPLE(CARDSET *cardset,CARDSET *cards)
//cardset���뵱ǰ����������ƣ�cards���뵱ǰ�ɳ�����
{
    CARD card={0,0},currentCard;
    int i,j,temp,isFunction=0;
    int count_Function=0,count_Num=0;
    int count_Color[5],array[5]={0,1,2,3,4};

    /*��ǰ�����ҽ���һ���ƿ��Գ���������*/
    if(cards->size==1)
        return cards->cards[0];

    /*ͳ�Ƶ�ǰ��������е�������*/
    for(i=0;i<=cardset->size-1;i++){
        currentCard=cardset->cards[i];
        /*ͳ�������й����Ƶı���*/
        if(currentCard.name<=16&&currentCard.name>=12)
            count_Function++;
        else
            count_Num++;

        /*ͳ�������и�����ɫ�Ƶı���*/
        count_Color[currentCard.color]++;
    }

    for(i=0;i<=3;i++){   //ð�������������ɫ�ư��������еݼ�����
        for(j=1;j<=3;j++){
            if(count_Color[j]<count_Color[j+1]){
                temp=array[j];         //array������Ϊ��ɫ
                array[j]=array[j+1];   //array�����д�Ŵ�С˳��
                array[j+1]=temp;
            }
        }              //������Ϊarray�����д������ԽС����Ӧ��ɫӵ����Խ��
    }

        /*�жϵ�ǰ����ܴ���������Ƿ��й�����*/
    for(j=0;j<=cards->size-1;j++){
        currentCard=cards->cards[j];
        if(currentCard.name>=12&&currentCard.name<=16)
            isFunction=1;
    }


    /*�������ճ��ƵĲ���*/
    if(isFunction==1&&count_Function>=count_Num){  //�й����ƿɳ����ʺϳ�������ʱ
        for(j=0;j<=cards->size-1;j++){             //ɸѡ����ʵĳ���
            currentCard=cards->cards[j];
            if(currentCard.name>=12&&currentCard.name<=16){
                if(currentCard.name==16){
                    if(card.color==0&&card.name==0) //����+4�Ƶĳ��Ƶ����ȼ�
                        card=currentCard;
                }
                else
                    card=currentCard;
            }
        }
    }
    else{  //�������ֻ�ܳ�������
        for(j=0;j<=cards->size-1;j++){
            currentCard=cards->cards[j];
            if(j==0)
                card=currentCard;
            else{
                if(array[currentCard.color]<card.color)  //ѡ�����������ɫ���Ƚ��г���
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