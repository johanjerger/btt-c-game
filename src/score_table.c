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
#include <string.h>
#include <errno.h>
#include "include/error.h"
#include "include/types.h"
#include "include/function.h"


	static void read_score_table(char * _home, score * imp_table)
	{
		FILE * score_table;
		score score_row;
		short i;

		if((score_table = fopen(_home, "r+")) == NULL){
			fprintf(stderr, "error -> %d\n", errno);
			exit(ERR_OPEN_FILE);
		}

		for(i = 0; i < TB; i++){
			if((fread(&score_row.name, 1, sizeof(score_row.name), score_table)) == 0){
				fprintf(stderr, "error -> %d\n", EIO);
				exit(ERR_READ_FILE);
			}
      if((fread(&score_row.point, 1, sizeof(score_row.point), score_table)) == 0){
      	fprintf(stderr, "error -> %d\n", EIO);
      	exit(ERR_READ_FILE);
      }
	    if((fread(&score_row.level, 1, sizeof(score_row.level), score_table)) == 0){
				fprintf(stderr, "error -> %d\n", EIO);
				exit(ERR_READ_FILE);
			}
      imp_table[i] = score_row;
		}
		fclose(score_table);
	}


	static void printf_score_tab(score * imp_table, short actual_score_tab)
	{
		short i;

		switch(actual_score_tab){
			case EASY:
				printf(BLUE "\t\t\tEASY SCORE TAB\n\n" RESET);
				break;
			case NORMAL:
				printf(BLUE "\t\t\tNORMAL SCORE TAB\n\n" RESET);
				break;
			case HARD:
				printf(BLUE "\t\t\tHARD SCORE TAB\n\n" RESET);
				break;
			case VERY_HARD:
				printf(BLUE "\t\t\tVERY HARD SCORE TAB\n\n" RESET);
				break;
			case HOPELESS:
				printf(BLUE "\t\t\tHOPELESS SCORE TAB\n\n" RESET);
				break;
		}

		printf(YELLOW "%-10s" BLUE "     ---     " YELLOW "%-10s" BLUE "     ---     " YELLOW "%-10s\n" RESET, " name", " score", " level");
		for(i = 0; i < TB; i++){
			printf("%-10s     " BLUE "---" RESET "     %10d     " BLUE "---" RESET "     %10d     \n" RESET, imp_table[i].name, imp_table[i].point, imp_table[i].level);
		}
	}


	short create_score_tab(char * _home)
	{
		FILE * score_table;
		score score_row;
		short i;

		if((score_table = fopen(_home, "w+")) == NULL){
			fprintf(stderr, "error -> %d\n", errno);
			exit(ERR_CREATING_FILE);
		}
		for(i = 0; i < TB; i++){
			strcpy(score_row.name, " ----- ");
			score_row.point = 0;
			score_row.level = 1;
			fwrite(&score_row.name, sizeof(score_row.name), 1, score_table);
			fwrite(&score_row.point, sizeof(score_row.point), 1, score_table);
			fwrite(&score_row.level, sizeof(score_row.level), 1, score_table);
		}
		fclose(score_table);

		return 0;
	}


	short score_tab(char * _home, short actual_score_tab)
	{
		FILE * score_table;
		score imp_table[TB];

		clear();
		if((score_table = fopen(_home, "r+")) == NULL){
			create_score_tab(_home);
		} else {
			fclose(score_table);
		}
		read_score_table(_home, imp_table);
		if((score_table = fopen(_home, "r+")) == NULL){
			fprintf(stderr, "error -> %d\n", errno);
			exit(ERR_OPEN_FILE);
		}
		printf_score_tab(imp_table, actual_score_tab);
		fclose(score_table);

		return 0;
	}


	short is_high_score(int point, int level, int game_difficulty)
	{
		FILE * score_table;
		score imp_table[TB];
		char aux[1024], aux_name[1024];
		short i, j, c, pos = TB, aux_point = 0, aux_level = 1;
		char _home[1024];

		strcpy(_home, getenv("HOME"));
		strcat(_home, "/.btt");
		switch(game_difficulty){
			case EASY:
				strcat(_home, "EasyScoreTab");
				break;
			case NORMAL:
				strcat(_home, "NormalScoreTab");
				break;
			case HARD:
				strcat(_home, "HardScoreTab");
				break;
			case VERY_HARD:
				strcat(_home, "VeryHardScoreTab");
				break;
			case HOPELESS:
				strcat(_home, "HopelessScoreTab");
				break;
		}

		if((score_table = fopen(_home, "r+")) == NULL){
			create_score_tab(_home);
		} else {
			fclose(score_table);
		}

		read_score_table(_home, imp_table);

		aux[0] = ' ';

		printf("\n\t\t\tpress " GREEN "ENTER" RESET "\n");
		while((getchar())!='\n');

		for(i = 0, j = 1; i < TB; i++){
			if(point >= imp_table[i].point){
				if(point == 0){
					j = 8;
					break;
				}
				pos = i;
				printf("Congrats your score is the number %d of the list\n", i+1);
				printf("Put your name [10 char]: <default: 'Stallman'>\n");
				while(((c = getchar()) != 10) && (j < 10)){
					aux[j++] = c;
				}
				aux[j]='\0';

				break;
			}
		}

		if(j == 1){
			aux[1] = 'S';
			aux[2] = 't';
			aux[3] = 'a';
			aux[4] = 'l';
			aux[5] = 'l';
			aux[6] = 'm';
			aux[7] = 'a';
			aux[8] = 'n';
			aux[9] = '\0';
		}

		c = kbhit();
		if(c != 0){
			c = kbhit();
		}

		for(; pos < TB; pos++){
			strcpy(aux_name, imp_table[pos].name);
			aux_point = imp_table[pos].point;
			aux_level = imp_table[pos].level;
			strcpy(imp_table[pos].name, aux);
			imp_table[pos].point = point;
			imp_table[pos].level = level;
			strcpy(aux, aux_name);
			point = aux_point;
			level = aux_level;
		}

		if((score_table = fopen(_home, "r+")) == NULL){
			fprintf(stderr, "error -> %d\n", errno);
			exit(ERR_OPEN_FILE);
		}
		for(i = 0; i < TB; i++){
			fwrite(&imp_table[i].name, sizeof(imp_table[i].name), 1, score_table);
			fwrite(&imp_table[i].point, sizeof(imp_table[i].point), 1, score_table);
			fwrite(&imp_table[i].level, sizeof(imp_table[i].level), 1, score_table);
		}
		fclose(score_table);
		clear();
		printf_score_tab(imp_table, game_difficulty);
		printf("\n");
		printf("\n\t\t\t\tpress " GREEN "ENTER" RESET "\n");
		while((getchar())!='\n');

		return 0;
	}
