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
#include <ctype.h>
#include "include/types.h"
#include "include/function.h"
#include "include/score_table.h"


	short printf_menu()
	{
		clear();
		printf(RED "\t\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" RESET);
		printf(RED "\t\tXX" YELLOW "X                                      X" RED "XX\n" RESET);
		printf(RED "\t\tXX" BLUE "    XXXXXXX    XXXXXXXX     XXXXXXXX    " RED "XX\n" RESET);
		printf(RED "\t\tXX" BLUE "    XX   XXX      XX           XX       " RED "XX\n" RESET);
		printf(RED "\t\tXX" BLUE "    XXXXXXX       XX           XX       " RED "XX\n" RESET);
		printf(RED "\t\tXX" BLUE "    XX   XXX      XX           XX       " RED "XX\n" RESET);
		printf(RED "\t\tXX" BLUE "    XXXXXXX       XX           XX       " RED "XX\n" RESET);
		printf(RED "\t\tXX" YELLOW "X                                      X" RED "XX\n" RESET);
		printf(RED "\t\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n\n" RESET);

		return 0;
	}


	static void footbar_menu()
	{
		printf("\tUse the 'w' & 's' to switch the select option - press " GREEN "ENTER" RESET " to select\n\t\t\t\t\t\t\t  " CYAN "Version %s\n\n" RESET, VERSION);
	}


	static int history(short * actual_page)
	{
		int pages;
		char c;
		pages = (int) max_score() /  100;
		if(pages > 9)
		{
			pages = 9;
		}
		clear();
 		printf_menu();
		switch (*actual_page) {
			case PAGE1:
				printf("\t\t\tIn the year 2057, an UFO descended\n\t\t\ton planet earth, infecting the entire\n\t\t\tplanet with " RED "cannibal orphans" RESET " with cold\n\t\t\tand mean feelings as a dead elephant.\n\n\t\t\tYou are the " BLUE "choosen one"RESET" to defend\n\t\t\tthe planet from evil " RED "cannibal orphans" RESET ".\n\n\t\t\tGrab your weaponds and go for them!\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE2:
				printf("\t\t\tTwo months have passed since the\n\t\t\tUFO descended. You and your squad have\n\t\t\tfound small hints indicating that the \n\t\t\t" RED "enemy base" RESET" is nearby.\n\n\t\t\tThe " RED "Cannibal orphans" RESET " have stolen all\n\t\t\tthe mothers of " BLUE "planet earth" RESET ",\n\t\t\tso that at last someone treats\n\t\t\tthem as people, unfortunately, the\n\t\t\tPhaders didn't have the same fate...\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE3:
				printf("\t\t\tYou finally found the enemy base, looking\n\t\t\tat it from a hill you see how the " RED "cannibal" RESET "\n\t\t\t" RED "orphans" RESET " violently rape the motehrs in\n\t\t\torder to reproduce and dominate \n\t\t\t" BLUE "planet earth" RESET ".\n\n\t\t\tNot only the mothers, You see as there\n\t\t\tare also helpless girls. " BLUE "You an your" RESET "\n\t\t\t" BLUE "squad" RESET " are subjected to hear those\n\t\t\tcries of pain and see that tears.\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE4:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE5:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE6:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE7:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE8:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE9:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
			case PAGE10:
				printf("\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
		}
		printf("\n\tUse the 'a' & 'd' to switch the differents history pages\t page %d/%d\n", (*actual_page) + 1, pages + 1);
		do {
			c = getch();
		} while ( c != 10 && c != 'a' && c != 'd');
		c = tolower(c);
		if(c == 10){
			return 0;
		} else if (c == 'a') {
			if((*actual_page) != PAGE1){
				(*actual_page)--;
			} else {
				(*actual_page) = pages;
			}
		} else if (c == 'd') {
			if((*actual_page) != pages){
				(*actual_page)++;
			} else {
				(*actual_page) = PAGE1;
			}
		}

		return history(actual_page);
	}


	static void tutorial()
	{
		printf_menu();
		printf("\t\t\t\t " BLUE "TUTORIAL" RESET "\n\n\t\t\t\t'a' " RED "~>" RESET " Left\n\t\t\t\t'd' " RED "~>" RESET " Right\n\t\t\t\t'w' " RED "~>" RESET " Up\n\t\t\t\t's' " RED "~>" RESET " Down\n\t\t\t\t'k' " RED "~>" RESET " shots\n\t\t\t\t'p' " RED "~>" RESET " pause\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
		while(getch() != 10);
		clear();
	}


	static short start_game_menu(int actual_difficulty)
	{
		short c;

		printf_menu();
		printf("\t\t\t\tSelect Difficulty\n\n");
		switch(actual_difficulty){
			case EASY:
				printf(YELLOW "\t\t\t\t Easy " RESET "\n\t\t\t\t Normal \n\t\t\t\t Hard \n\t\t\t\t Very hard \n\t\t\t\t Hopeless \n\n");
				break;
			case NORMAL:
				printf("\t\t\t\t Easy \n\t\t\t\t" YELLOW " Normal " RESET "\n\t\t\t\t Hard \n\t\t\t\t Very hard \n\t\t\t\t Hopeless \n\n");
				break;
			case HARD:
				printf("\t\t\t\t Easy \n\t\t\t\t Normal \n\t\t\t\t" YELLOW " Hard " RESET "\n\t\t\t\t Very hard \n\t\t\t\t Hopeless \n\n");
				break;
			case VERY_HARD:
				printf("\t\t\t\t Easy \n\t\t\t\t Normal \n\t\t\t\t Hard \n\t\t\t\t" YELLOW " Very hard \n\t\t\t\t" RESET " Hopeless \n\n");
				break;
			case HOPELESS:
				printf("\t\t\t\t Easy \n\t\t\t\t Normal \n\t\t\t\t Hard \n\t\t\t\t Very hard \n\t\t\t\t" YELLOW " Hopeless \n\n" RESET );
				break;
		}
		footbar_menu();
		do {
			c = getch();
		} while ( c != 10 && c != 's' && c != 'w');
		c = tolower(c);
		if(c == 10){
			return actual_difficulty;
		} else if(c == 'w'){
			if(actual_difficulty != EASY){
				actual_difficulty--;
			} else {
				actual_difficulty = HOPELESS;
			}
		} else if (c == 's'){
			if(actual_difficulty != HOPELESS){
				actual_difficulty++;
			} else {
				actual_difficulty = EASY;
			}
		}
		return start_game_menu(actual_difficulty);
	}


	static short score_tab_menu(short * actual_score_tab_option, short * actual_score_tab)
	{
		short c;
		clear();
		char _home[1024];

		strcpy(_home, getenv("HOME"));
		strcat(_home, "/.bttConfig/btt");
		switch(*actual_score_tab){
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

		score_tab(_home, *actual_score_tab);
		switch(*actual_score_tab_option){
			case MENU:
				printf(YELLOW "\n\t\t\t       Back to Menu " RESET "\n\t\t\t       Reset Table \n\n\n");
				break;
			case CLEAN:
				printf("\n\t\t\t       Back to Menu \n\t\t\t" YELLOW "       Reset Table \n\n\n" RESET);
				break;
		}
		printf("\tUse the 'a' & 'd' to switch the differents score tables\n");
		footbar_menu();
		do {
			c = getch();
		} while ( c != 10 && c != 's' && c != 'w' && c != 'a' && c != 'd');
		c = tolower(c);
		if(c == 10){
			return 0;
		} else if(c == 'w'){
			if((*actual_score_tab_option) != MENU){
				(*actual_score_tab_option)--;
			} else {
				(*actual_score_tab_option) = CLEAN;
			}
		} else if (c == 's'){
			if((*actual_score_tab_option) != CLEAN){
				(*actual_score_tab_option)++;
			} else {
				(*actual_score_tab_option) = MENU;
			}
		} else if (c == 'a') {
			if((*actual_score_tab) != EASY){
				(*actual_score_tab)--;
			} else {
				(*actual_score_tab) = HOPELESS;
			}
		} else if (c == 'd') {
			if((*actual_score_tab) != HOPELESS){
				(*actual_score_tab)++;
			} else {
				(*actual_score_tab) = EASY;
			}
		}
		return score_tab_menu(actual_score_tab_option, actual_score_tab);
	}


	short pause_messege(short actual_pause_option, short * quit)
	{
		short c;
		printf_menu();
		printf("\n\t\t\t\t" BLUE "   PAUSE" RESET "\n\n");
		switch(actual_pause_option){
			case RESUME:
				printf(YELLOW "\t\t\t\tResume Game " RESET "\n\t\t\t\tGo to Menu \n\n\n\n");
				break;
			case QUIT:
				printf("\t\t\t\tResume Game \n\t\t\t\t" YELLOW "Go to Menu \n\n\n\n" RESET);
				break;
		}
		footbar_menu();
		do {
			c = getch();
		} while ( c != 10 && c != 's' && c != 'w');
		c = tolower(c);
		if(c == 10){
			switch(actual_pause_option){
				case RESUME:
					return 0;
					break;
				case QUIT:
					*quit = 1;
					return 0;
					break;
			}
		} else if(c == 'w'){
			if(actual_pause_option != RESUME){
				actual_pause_option--;
			} else {
				actual_pause_option = QUIT;
			}
		} else if (c == 's'){
			if(actual_pause_option != QUIT){
				actual_pause_option++;
			} else {
				actual_pause_option = RESUME;
			}
		}

		return pause_messege(actual_pause_option, quit);
	}


	short menu(short actual_option)
	{
		short c, actual_page = PAGE1, actual_difficulty = EASY, actual_score_tab_option = MENU, actual_score_tab = EASY;
		char _home[256];
		printf_menu();
		switch(actual_option){
			case START_GAME:
				printf(YELLOW "\t\t\t\t Start Game " RESET "\n\t\t\t\t Score Tab \n\t\t\t\t History \n\t\t\t\t Tutorial \n\t\t\t\t Exit \n\n\n\n");
				break;
			case SCORE_TAB:
				printf("\t\t\t\t Start Game \n\t\t\t\t" YELLOW " Score Tab " RESET "\n\t\t\t\t History \n\t\t\t\t Tutorial \n\t\t\t\t Exit \n\n\n\n" RESET);
				break;
			case HISTORY:
				printf("\t\t\t\t Start Game \n\t\t\t\t Score Tab \n\t\t\t\t" YELLOW " History " RESET "\n\t\t\t\t Tutorial \n\t\t\t\t Exit \n\n\n\n" RESET);
				break;
			case TUTORIAL:
				printf("\t\t\t\t Start Game \n\t\t\t\t Score Tab \n\t\t\t\t History \n\t\t\t\t" YELLOW " Tutorial " RESET "\n\t\t\t\t Exit \n\n\n\n" RESET);
				break;
			case EXIT:
				printf("\t\t\t\t Start Game \n\t\t\t\t Score Tab \n\t\t\t\t History \n\t\t\t\t Tutorial \n\t\t\t\t" YELLOW " Exit " RESET "\n\n\n\n" RESET);
				break;
		}
		footbar_menu();
		do {
			c = getch();
		} while ( c != 10 && c != 's' && c != 'w');
		c = tolower(c);
		if(c == 10){
			switch(actual_option){
				case START_GAME:
					return start_game_menu(actual_difficulty);
					break;
				case SCORE_TAB:
					score_tab_menu(&actual_score_tab_option, &actual_score_tab);
					if(actual_score_tab_option == CLEAN){
						strcpy(_home, getenv("HOME"));
						strcat(_home, "/.bttConfig/btt");
						switch(actual_score_tab){
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
						create_score_tab(_home);
					}
					break;
				case HISTORY:
					history(&actual_page);
					break;
				case TUTORIAL:
					tutorial();
					break;
				case EXIT:
					return 'q';
					break;
			}
		} else if(c == 'w'){
			if(actual_option != START_GAME){
				actual_option--;
			} else {
				actual_option = EXIT;
			}
		} else if (c == 's'){
			if(actual_option != EXIT){
				actual_option++;
			} else {
				actual_option = START_GAME;
			}
		}

		return menu(actual_option);
	}


	short select_player(short actual_player)
	{
		short c;
		printf_menu();
		printf("\t\t\t\tSelect a Player\n\n");
		switch(actual_player){
			case FIRST:
				printf(YELLOW "\t\t\t\t     * " RESET "\n\t\t\t\t     ~ \n\t\t\t\t     + \n\n\n\n");
				break;
			case SECOND:
				printf("\t\t\t\t     * \n\t\t\t\t" YELLOW "     ~ " RESET "\n\t\t\t\t     + \n\n\n\n");
				break;
			case THIRD:
				printf("\t\t\t\t     * \n\t\t\t\t     ~ \n\t\t\t\t" YELLOW "     + " RESET "\n\n\n\n");
				break;
		}
		footbar_menu();
		do {
			c = getch();
		} while ( c != 10 && c != 's' && c != 'w');
		c = tolower(c);
		if(c == 10){
			switch(actual_player){
				case FIRST:
					return '*';
					break;
				case SECOND:
					return '~';
					break;
				case THIRD:
					return '+';
					break;
			}
		} else if(c == 'w'){
			if(actual_player != FIRST){
				actual_player--;
			} else {
				actual_player = THIRD;
			}
		} else if (c == 's'){
			if(actual_player != THIRD){
				actual_player++;
			} else {
				actual_player = FIRST;
			}
		}
		return select_player(actual_player);
	}
