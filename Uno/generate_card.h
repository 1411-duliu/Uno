#ifndef GEN_CARD_H
#define GEN_CARD_H
// #include "uno.h"

CARD * generateCards(); // ���ɳ�ʼ����
void shuffleCards(CARD * cards); // ϴ��
void getIntoCardset(CARDSET * cardset, CARD * cards, int size); // ��CARD�������CARDSET������
void distributeCards(CARDSET cardset[], CARDSET from, int num); // ���Ʒ������
STATE init_state();
#endif