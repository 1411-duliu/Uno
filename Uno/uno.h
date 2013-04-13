#ifndef UNO_H
#define UNO_H

#define NONE 	10
#define CALL		11
#define REVERSE	12
#define SKIP		13
#define PLUS_2	14
#define WILD		15
#define PLUS_4	16

#define CNONE	0
#define GREEN	1
#define RED		2
#define	YELLOW	3
#define	BLUE		4
#define INVALID	1411

#define PLAYER_NUM	4
#define HUMAN		1
#define MAX_MSG_NUM 4

#define ROUND_START	1
#define PLAY_CARD	2
#define	SETTLE		3
#define ROUND_END	4
#define	GAME_END		5

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

struct MsgListNode {
	char * msg;
	struct MsgListNode * nextPtr;
};

typedef struct Card CARD;
typedef struct CardSet CARDSET;
typedef struct State STATE;
typedef struct MsgListNode MSGLISTNODE;
typedef MSGLISTNODE * MSGLISTNODEPTR;

#endif
