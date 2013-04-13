#ifndef UTILITIES_H
#define UTILITIES_H
void printEntityCards(CARDSET CARDS[]); // ��ӡ��������
char * cardToStr(CARD card); // ��CARD����ת��Ϊ�ַ���
char * playCardMsg(int player, CARD card);
void printCardset(CARDSET cardset);
void printGameState(STATE game_state);
int isSameCards(CARD card1, CARD card2);
char * callCardMsg(int player, int n);
char * colorToStr(int color);
int strToColor(char * str);
#endif