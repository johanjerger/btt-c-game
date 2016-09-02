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
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "include/error.h"
#include "include/types.h"


	int getch(void)
	{
		struct termios oldattr, newattr;
		int ch;
		tcgetattr(1, &oldattr);
		newattr = oldattr;
		newattr.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(1, TCSANOW, &newattr);
		ch = getchar();
		tcsetattr(1, TCSANOW, &oldattr);
		return ch;
	}


	int kbhit(void)
	{
		struct termios oldt, newt;
		char ch[20];
		int oldf;

		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

		if((scanf("%s", ch)) == 0){
			fprintf(stderr, "error -> %d\n", EIO);
			exit(ERR_READ_SCAN);
		}

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);

		if(ch[0] != EOF) return ch[0];

		return 0;
	}


	int menu()
	{
		int dif;

		if((system("clear")) == -1) exit(ERR_SYS);
		
		printf("Main Menu :\n\n\t1 -> Easy\n\t2 -> Normal\n\t3 -> Hard\n\t4 -> Very Hard\n\tt -> Tutorial\n\th -> History\n\tq -> exit\n\n");
		dif = getch();
		switch(dif){
		case '1': 
			printf("\nEasy mode Selected\nLoading,...\n");
			break;
		case '2': 
			printf("\nNormal mode Selected\nLoading,...\n");
			break;
		case '3': 
			printf("\nHard mode Selected\nLoading,...\n");
			break;
		case '4': 
			printf("\nVery Hard mode Selected\nLoading,...\n");
			break;
		case 't': 
			if((system("clear")) == -1) exit(ERR_SYS);

			printf("\t TUTORIAL\n\n\t'a' -> Left\n\t'd' -> Right\n\t'w' -> Up\n\t's' -> Down\n\t'k' -> shots\n\t'q' -> quit\n");
			printf("\n\n\tPress ENTER\n");
			getchar();
			if((system("clear")) == -1) exit(ERR_SYS);

			dif = menu();
			break;
		case 'h': 
			if((system("clear")) == -1)	exit(ERR_SYS);
			
			printf("\tIn the year 2057, an UFO descended\n\ton planet earth, infecting the entire\n\tplanet with cannibal orphans with\n\tcold and mean feelings as a\n\tdead elephant.\n\tYou are the choosen one to\n\tdefend the planet from evil\n\tcannibal orphans.\n\tGrab your weaponds and go for\n\tthem!\n");
			printf("\n\n\tPress ENTER\n");
			getchar();
			if((system("clear")) == -1) exit(ERR_SYS);
	
			dif = menu();
			break;
		case 'q':
			break;
		default: 
			printf("\nIncorrect Option, Easy mode Selected\nLoading,...\n");
			dif = '1';
			break;
		}
		if(dif != 'q'){
			sleep(2.5);
		}
		if((system("clear")) == -1) exit(ERR_SYS);


		return dif;
	}


	char select_pj()
  	{
		int c;
		if((system("clear")) == -1)	exit(ERR_SYS);

		printf("Select your Character:\n");
		printf("\n\t1 -> *\n\t2 -> %c\n\t3 -> +\n\n", 126);
		c = getch();
		switch(c){
			case '1':
				return '*';
			case '2':
				return 126;
			case '3':
				return '+';
			default:
				return '*';
		}
	}


	int initialize_area(block * area)
	{
		int i;
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


	int draw(block_arr area)
	{
		int i, j;

		if((system("clear")) == -1) exit(ERR_SYS);

		for(i = 0; i < L; i++){
			j = 0;
			printf(MAGENTA "%c" RESET, '|');
			for(j = 1; j < A-1; j++){
				if(area[i][j].c == '#'){
					printf(GREEN "%c" RESET, area[i][j].c);
				} else if((area[i][j].c == '*') || (area[i][j].c == 126) || (area[i][j].c == '+')){
					printf(CYAN "%c" RESET, area[i][j].c);
				} else if(area[i][j].c == 'x'){
					printf(RED "%c" RESET, area[i][j].c);
				} else if(area[i][j].c == '-'){
					printf(BLUE "%c" RESET, area[i][j].c);
				} else {
					printf(MAGENTA "%c" RESET, area[i][j].c);
				}
			}
			printf("%c\n", '|');
		}

		return 0;
	}


	int is_high_score(int point)
	{
		FILE * score_tb;
		score imp_table[TB];
		score sc;
		char aux[256], aux_name[256];
		int i, j, c, pos = TB, aux_score;

		if((score_tb = fopen("scoreTab", "r+")) == NULL){
			score_tb = fopen("scoreTab", "w+");
			for(i = 0; i < TB; i++){
				strcpy(sc.name, " ----- ");
				sc.point = 0;
				fwrite(&sc.name, sizeof(sc.name), 1, score_tb);
				fwrite(&sc.point, sizeof(sc.point), 1, score_tb);
			}
			rewind(score_tb);
		}

		for(i = 0; i < TB; i++){
			if((fread(&sc.name, 1, sizeof(sc.name), score_tb)) == 0){
				fprintf(stderr, "error -> %d\n", EIO);
				exit(ERR_READ_FILE);
			}
	        if((fread(&sc.point, 1, sizeof(sc.point), score_tb)) == 0){
	        	fprintf(stderr, "error -> %d\n", EIO);
	        	exit(ERR_READ_FILE);
	        }
	        imp_table[i] = sc;
		}

		aux[0] = ' ';

		for(i = 1, j = 1; i < TB; i++){
			if(point >= imp_table[i].point){
				pos = i;
				printf("Congrats your score is the number %d of the list\n", i+1);
				printf("Put your name : \n");
				while(((c = getchar()) != 10) && (j < 10)){
					aux[j++] = c;
				}

				break;
			}
		}

		for(; pos < TB; pos++){
			strcpy(aux_name, imp_table[pos].name);
			aux_score = imp_table[pos].point;
			strcpy(imp_table[pos].name, aux);
			imp_table[pos].point = point;
			strcpy(aux, aux_name);
			point = aux_score;
		}

		rewind(score_tb);
		for(i = 0; i < TB; i++){
			fwrite(&imp_table[i].name, sizeof(imp_table[i].name), 1, score_tb);
			fwrite(&imp_table[i].point, sizeof(imp_table[i].point), 1, score_tb);
		}

		fclose(score_tb);

		if((system("clear")) == -1) exit(ERR_SYS);

		printf("               SCORE TAB\n\n");
		for(i = 0; i < TB; i++){
			printf("%-15s ------ %15d\n", imp_table[i].name, imp_table[i].point);
		}

		printf("\n");

		return 0;
	}