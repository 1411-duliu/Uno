#ifndef UTILITIES_H
#define UTILITIES_H
void printEntityCards(CARDSET CARDS[]); // 打印所有牌组
char * cardToStr(CARD card); // 将CARD类型转换为字符串
char * playCardMsg(int player, CARD card);
void printCardset(CARDSET cardset);
void printGameState(STATE game_state);
int isSameCards(CARD card1, CARD card2);
char * callCardMsg(int player, int n);
char * colorToStr(int color);
int strToColor(char * str);
#endif