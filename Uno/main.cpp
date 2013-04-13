#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "uno.h"
#include "game_main.h"

int main(int argc, const char * argv[])
{
	FILE * fp = fopen("log.txt", "w+");
	fprintf(fp, "New Log By Uno \n\n");
	fclose(fp);

	main_loop();

	system("pause");
    return 0;
}
