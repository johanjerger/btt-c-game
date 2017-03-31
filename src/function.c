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
#include "include/error.h"
#include "include/types.h"


	short clear()
	{
		if((system("clear")) == -1){
			fprintf(stderr, "error -> %d\n", errno);
			exit(ERR_SYS);
		}

		return 0;
	}


	short _nanosleep(int time)
	{
		/*
			timespec struct is use for
			every "sleep" time during
			the game.
		*/

		struct timespec ts;
	  	ts.tv_sec = time / 1000;
	  	ts.tv_nsec = (time % 1000) * 1000000;

		if((nanosleep(&ts, NULL)) == -1){
			fprintf(stderr, "error -> %d\n", errno);
			exit(ERR_SYS);
		}

		return 0;
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
		return ch;
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

		if(!(scanf("%s", ch))){
			fprintf(stderr, "error -> %d\n", EIO);
			exit(ERR_READ_SCAN);
		}

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);

		if(ch[0] != EOF){
			return ch[0];
		}

		return 0;
	}


	short initialize_area(block * area)
	{
		short i;
		area[0].c = '|';
		area[0].pos = 0;
		for(i = 1; i < A - 1; i++){
			area[i].c = ' ';
			area[i].pos = i;
		}
		area[A-1].c = '|';
		area[A-1].pos = A - 1;
		area[A].c = '\0';
		area[A].pos = A;
		return 0;
	}


	short draw(block_arr area)
	{
		short i, j, top = A-1;
		char ch;
		clear();
		for(i = 0; i != L; i++)
		{
			printf(MAGENTA "|" RESET);
			for(j = 1; j != top; j++)
			{
				ch = area[i][j].c;
				switch (ch)
				{
					case ' ':
						printf(" "); break;
					case '#':
						printf(GREEN "#"); break;
					case '-':
						printf(BLUE "-"); break;
					case 'x':
						printf(RED "X"); break;
					default:
						printf(CYAN "%c", ch); break;
				}
			}
			printf(MAGENTA "|\n" RESET);
		}
		for(j = 0; j < A; j++){
			printf(CYAN "‾" RESET);
		}

		return 0;
	}
