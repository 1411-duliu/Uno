#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "uno.h"
#include "game_main.h"

int main(int argc, const char * argv[])
{
	main_loop(); // 进入游戏主循环

	system("pause");
    return 0;
}
