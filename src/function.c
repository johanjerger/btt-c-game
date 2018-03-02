/***************************************************************************
*
*				 «©Copyright 2016 Juan Cruz Ocampos»
*
*	 This file is part of btt.
*
*    btt is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    btt is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with btt.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "include/error.h"
#include "include/types.h"


void clear()
{
		if((system("clear")) == -1)
		{
				fprintf(stderr, "error -> %d\n", errno);
				exit(ERR_SYS);
		}
}

//  timespec struct is use for every "sleep" time during the game.
void _nanosleep(int time)
{
		struct timespec ts;
		ts.tv_sec = time / 1000;
		ts.tv_nsec = (time % 1000) * 1000000;

		if((nanosleep(&ts, NULL)) == -1)
		{
				fprintf(stderr, "error -> %d\n", errno);
				exit(ERR_SYS);
		}
}

short getch(void)
{
		struct termios oldattr, newattr;
		short ch;
		tcgetattr(1, &oldattr);
		newattr = oldattr;
		newattr.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(1, TCSANOW, &newattr);
		ch = getchar();
		tcsetattr(1, TCSANOW, &oldattr);
		return tolower(ch);
}

short kbhit(void)
{
		struct termios oldt, newt;
		char ch[20];
		short oldf;

		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

		if(!(scanf("%s", ch))) {
				fprintf(stderr, "error -> %d\n", EIO);
				exit(ERR_READ_SCAN);
		}

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);

		if(ch[0] != EOF) {
				return tolower(ch[0]);
		}

		return 0;
}

void initialize_area(block * area)
{
		area[0].c = '|';
		area[0].pos = 0;
		for(int i = 1; i < A - 1; i++)
		{
				area[i].c = ' ';
				area[i].pos = i;
		}
		area[A-1].c = '|';
		area[A-1].pos = A - 1;
		area[A].c = '\0';
		area[A].pos = A;
}

void draw(block_arr area)
{
		clear();
		for(int i = 0; i != AREA_HEIGHT; i++)
		{
				printf(MAGENTA "|" RESET);
				for(int j = 1; j != A-1; j++)
				{
						switch (area[i][j].c)
						{
						case ' ':
								printf(" ");
								continue;
						case '#':
								printf(GREEN "#");
								continue;
						case '-':
								printf(BLUE "-");
								continue;
						case 'x':
								printf(RED "X");
								continue;
						default:
								printf(CYAN "%c", area[i][j].c);
						}
				}
				printf(MAGENTA "|\n" RESET);
		}
		for(int j = 0; j < A; j++)
		{
				printf(CYAN "‾" RESET);
		}
}
