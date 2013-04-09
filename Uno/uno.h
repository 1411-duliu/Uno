#ifndef UNO_H
#define UNO_H

#define NONE 	10
#define CALL		11
#define REVERSE	12
#define SKIP		13
#define PLUS_2	14
#define WILD		15
#define PLUS_4	16

#define PLAYER_NUM	4

struct Card {
    int color;
    int name;
};

struct CardSet {
	struct Card cards[108];
	int size;
};

struct State {
	int direction;
	int player;
	int color;
	int last_card;
	int plus_two;
	int plus_four;
	int skip;
	int penalty;
};

typedef struct Card CARD;
typedef struct CardSet CARDSET;
typedef struct State STATE;

#endif
