#include <stdio.h>
#include <stdlib.h>

#include "uno.h"
#include "game_main.h"
#include "ai_Simple.h"

/*�ϸ��ӵ�AI��ͳ���Լ��͵�ǰ���Ͼ��棬
�������������ʤ���ȵ�ͬʱ���������Լ��ķ���*/
CARD AI_HARD(CARDSET *cardset,CARDSET *cards,STATE state,
			 CARDSET player_Card[5],CARDSET trash[5])
/*cardset���뵱ǰ����������ƣ�cards���뵱ǰ�ɳ����ƣ�state���뵱ǰ��Ϸ������״̬��
player_Card[5]��������������ƣ�������ֻ���������������������������������Ҿ������ƣ�*/
{
	CARD card;
	CARDSET current_Player_Card;
	int i,flag_of_uno;

	for(i=1;i<=4;i++){     //�жϳ����Ƿ����Ѿ�UNO�����
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


/*����1������������UNO���з�Ӧ���������ͬ��*/
CARD Project1(CARDSET *cardset,CARDSET *cards,STATE state,
			 CARDSET player_Card[5],CARDSET trash[5])
{
	CARD card={0,11};
	int i,uno_Player,ifReverse=0;
	int nextPlayer=getNextPlayer(state);  //Ѱ����һλ���
	int previousPlayer=getPreviousPlayer(state); //Ѱ����һλ���

	CARDSET playerCard;
	playerCard=player_Card[nextPlayer];   

	if(playerCard.size==1){ //�¼���UNOʱ,���¼ҽ��в����˵��Ĺ���
		for(i=0;i<=cards->size-1;i++){  //�ӿɳ�������Ѱ����в�����ĳ��Ʒ���
			currentCard=cards->cards[i];
			if(currentCard.name==16)   //+4����
				card=currentCard;
			else if(currentCard.name==14&&card.name!=16)
				card=currentCard;     //+2���ȶȴ�֮
			else if(currentCard.name==13&&card.name!=16&&card.name!=14)
				card=currentCard;     //�����ٴ�֮
		}
		 
		if(card==(0,11)){    //��û�����������Ƶ�����½��н�һ��̽��
			for(i=0;i<=cards->size-1;i++){  //Ѱ���Ƿ���ת����
				currentCard=cards->cards[i];
				if(currentCard.name==12)
					ifReverse=1;
			}
			if(ifReverse==1&&previousPlayer.size!=1)
				card={0,12};  //�ڱ�֤��һ���δUNO���Լ���ת�򣬴��֮
			else{
				card=Analyze(trash[nextPlayer],trash[0],cards,state);
			}
		}
	}

	else{ //�¼�δUNO,�����������UNO����Ѱ��UNOĿ���������ƣ�
		 //��ȡ��֮��ͬ����ɫ����Զ��ѹ�ƣ���ʱ�����������������̵���
		
		for(i=2;i<=4;i++){     //�������Ѿ�UNO�����
			current_Player_Card=player_Card[i];	
			if(current_Player_Card.size==1)
				uno_Player=i;
		}
		card=Analyze(trash[uno_Player],trash[0],cards,state);//��������Զ�̴��
	}

	return card;
}


/*����2��������UNO����£��������������ͬ��*/
CARD Project2(CARDSET *cardset,CARDSET *cards,STATE state,
			 CARDSET player_Card[5],CARDSET trash[5])
{
	CARD card={0,11};
	int i;
	int nextPlayer=getNextPlayer(state);  //Ѱ����һλ���
	CARDSET playerCard;
	playerCard=player_Card[nextPlayer];   

	if(playerCard.size<=3)
	/*���¼�����<=3ʱ���Գ��Ʒ�������ѡ��
	  �ڿ�����������ͬʱ�������¼��ʵ�ѹ��
	  ��ʱ����+4��������˵�����*/
	{  
		for(i=0;i<=cards->size-1;i++){  //�ӿɳ�������Ѱ����в�����ĳ��Ʒ���
			currentCard=cards->cards[i];
			if(currentCard.name==14)   //+2����
				card=currentCard;
			else if(currentCard.name==13&&card.name!=14)
				card=currentCard;     //�������ȶȴ�֮

			if(card=={0,11}){
				card=Analyze(trash[nextPlayer],trash[0],cards,state)��
				if(card==0,11) //��û������ʵ��Ƶ����Լ����ܽ���
					card=ai_Simple(cardset,cards);
				               //�򰴶��Լ������ĳ��ƣ�û��Ҫ����
			}
	}

	else  //�����¼����н϶�����ʱ�����ռ�˼·������������������
		card=ai_Simple(cardset,cards);

	return card;
}

//----------------------------------------------------------------------


/*���ߺ�������*/
int getPreviousPlayer(STATE game_state)  
{               //��ǰ��ҵ�Ѱ��ǰһ�����
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
//����Ŀ����ҵ����ƶ�trash������������ƶѣ� ��ǰ���Գ�����
//��ֻ�ܳ���ͨ�ƺͱ�ɫ��ʱ��ͨ���������ƶѵó�����ѹ�ƽ�ǿ�����滨ɫ
//�˺������ó��Ŀ�����CALL��
{
	int i,bestColor,size,voidColor;
	CARD last_Card;//���Ŀ���������������
	CARD card={0,11};
	int * colors;

	size=playerTrash.size;
	last_Card=playerTrash.cards[size-1];
	voidColor=last_Card.color;

	for(i=0;i<=cards->size-1;i++){ 
		currentCard=cards->cards[i];
		if(currentCard.name==WILD)  //��ӵ�б�ɫ��ʱ���ȳ�
			card={bestColor,WILD};    //���ش��е�ǰ������ɫ�ı�ɫ��
		else if(currentCard.name!=WILD&&currentCard.color!=voidColor){
			if(colors[currentCard.color-1]<colors[card.color-1])
				card=currentCard;
		}

	}

	free(colors);
	return card;
}

int * countColor(CARDSET trash)
//����������ͳ�Ƶ�ǰ���ƶ��и�ɫ�Ƶı���
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

	for(i=1;i<=4;i++){   //ð�������Ŷ�����ɫ�Ĵ�С˳��
		for(j=1;j<=3;j++){
			if(colorCount[j]<colorCount[j+1]){
				temp=colorRank[j];
				colorRank[j]=colorRank[j+1];
				colorRank[j+1]=temp;
			}       //colorRank�д�ŵ��Ǹ���ɫ������˳��
		}           //����Խ��  ��Ӧ����Խ��
	}
	return colorRank;
}