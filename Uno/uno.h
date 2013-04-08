#define NONE 	10
#define CALL		20
#define REVERSE	100
#define SKIP		101
#define PLUS_2	102
#define WILD		200
#define PLUS_4	204

#define PLAYER_NUM	4

struct Card {
    int color;
    int name;
};

struct CardSet {
	struct Card cards[108];
	int size;
};

typedef struct Card CARD;
typedef struct CardSet CARDSET;