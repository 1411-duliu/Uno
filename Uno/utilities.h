#ifndef UTILITIES_H
#define UTILITIES_H
void printEntityCards(CARDSET CARDS[]); // 打印所有牌组
char * cardToStr(CARD card); // 将CARD类型转换为字符串
void printGameState(STATE game_state);
#endif