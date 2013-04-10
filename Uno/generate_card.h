#ifndef GEN_CARD_H
#define GEN_CARD_H
// #include "uno.h"

CARD * generateCards(); // 生成初始牌组
void shuffleCards(CARD * cards); // 洗牌
void getIntoCardset(CARDSET * cardset, CARD * cards, int size); // 将CARD数组放入CARDSET牌组中
void distributeCards(CARDSET cardset[], CARDSET from, int num); // 将牌发给玩家
STATE init_state();
#endif