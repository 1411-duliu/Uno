#ifndef UTILITIES_H
#define UTILITIES_H
void printEntityCards(CARDSET CARDS[]); // ��ӡ��������
char * cardToStr(CARD card); // ��CARD����ת��Ϊ�ַ���
char * playCardMsg(int player, CARD card);
void printCardset(CARDSET cardset);
void printGameState(STATE game_state);
#endif