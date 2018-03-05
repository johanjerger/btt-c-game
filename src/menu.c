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
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "include/types.h"
#include "include/menu_enums.h"
#include "include/function.h"
#include "include/score_table.h"
#include "include/game_title.h"

void printf_menu()
{
		clear();
		printf(BTT_TITLE RESET);
}


void footbar_menu()
{
		printf("\tUse the 'w' & 's' to switch the select option - press " GREEN "ENTER" RESET " to select\n\t\t\t\t\t\t\t  " CYAN "Version %s\n\n" RESET, VERSION);
}

void cmp_action(int * index, int min_index, int max_index, char comparable,
                char cmp_to_decrement, char cmp_to_increment)
{
		if (comparable == cmp_to_increment)
		{
				if ((*index) != min_index) (*index)--;
				else (*index) = max_index;
		}
		else if (comparable == cmp_to_decrement)
		{
				if ((*index) != max_index) (*index)++;
				else (*index) = min_index;
		}
}

int history(int index)
{
		int pages;
		pages = (int) max_score() /  100;
		if(pages > 9) pages = 9;
		clear();
		printf_menu();
		switch (index) {
		case PAGE1:
				printf("\t\t\tIn the year 2057, an UFO descended\n\t\t\ton planet earth, infecting the entire\n\t\t\tplanet with " RED "cannibal orphans" RESET " with cold\n\t\t\tand mean feelings as a dead elephant.\n\n\t\t\tYou are the " BLUE "choosen one"RESET " to defend\n\t\t\tthe planet from evil " RED "cannibal orphans" RESET ".\n\n\t\t\tGrab your weaponds and go for them!\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
				break;
		case PAGE2:
				printf("\t\t\tTwo months have passed since the\n\t\t\tUFO descended. You and your squad have\n\t\t\tfound small hints indicating that the \n\t\t\t" RED "enemy base" RESET " is nearby.\n\n\t\t\tThe " RED "Cannibal orphans" RESET " have stolen all\n\t\t\tthe mothers of " BLUE "planet earth" RESET ",\n\t\t\tso that at last someone treats\n\t\t\tthem as people, unfortunately, the\n\t\t\tPhaders didn't have the same fate...\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
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
		printf("\n\tUse the 'a' & 'd' to switch the differents history pages\t page %d/%d\n", (index) + 1, pages + 1);
		int c = 0;
		while ( c != 10 && c != 'a' && c != 'd') c = getch();
		if(c == 10) return 0;
		cmp_action(&index, PAGE1, pages, c, 'd', 'a');

		return history(index);
}


void tutorial()
{
		printf_menu();
		printf("\t\t\t\t " BLUE "TUTORIAL" RESET "\n\n\t\t\t\t'a' " RED "->" RESET " Left\n\t\t\t\t'd' " RED "->" RESET " Right\n\t\t\t\t'w' " RED "->" RESET " Up\n\t\t\t\t's' " RED "->" RESET " Down\n\t\t\t\t'k' " RED "->" RESET " shots\n\t\t\t\t'p' " RED "->" RESET " pause\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n");
		while(getch() != 10);
		clear();
}

short start_game_menu(int index)
{
		printf_menu();
		printf("\t\t\t\tSelect Difficulty\n\n");
		switch(index) {
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
		int c = 0;
		while ( c != 10 && c != 's' && c != 'w') c = getch();

		if (c == 10) return index;
		cmp_action(&index, EASY, HOPELESS, c, 's', 'w');

		return start_game_menu(index);
}


short score_tab_menu(int * actual_score_tab_option, int * actual_score_tab)
{
		clear();
		char _home[1024];

		strcpy(_home, getenv("HOME"));
		strcat(_home, "/.bttConfig/btt");
		switch(*actual_score_tab) {
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
		switch(*actual_score_tab_option) {
		case MENU:
				printf(YELLOW "\n\t\t\t       Back to Menu " RESET "\n\t\t\t       Reset Table \n\n\n");
				break;
		case CLEAN:
				printf("\n\t\t\t       Back to Menu \n\t\t\t" YELLOW "       Reset Table \n\n\n" RESET);
				break;
		}
		printf("\tUse the 'a' & 'd' to switch the differents score tables\n");
		footbar_menu();
		int c = 0;
		while ( c != 10 && c != 's' && c != 'w' && c != 'a' && c != 'd') c = getch();
		if (c == 10) return 0;
		cmp_action(actual_score_tab_option, MENU, CLEAN, c, 's', 'w');
		cmp_action(actual_score_tab, EASY, HOPELESS, c, 'd', 'a');

		return score_tab_menu(actual_score_tab_option, actual_score_tab);
}


bool pause_messege(int index)
{
		printf_menu();
		printf("\n\t\t\t\t" BLUE "   PAUSE" RESET "\n\n");
		switch(index) {
		case RESUME:
				printf(YELLOW "\t\t\t\tResume Game " RESET "\n\t\t\t\tGo to Menu \n\n\n\n");
				break;
		case QUIT:
				printf("\t\t\t\tResume Game \n\t\t\t\t" YELLOW "Go to Menu \n\n\n\n" RESET);
				break;
		}
		footbar_menu();
		int c = 0;
		while (c != 10 && c != 's' && c != 'w') c = getch();
		if (c == 10) return (index == QUIT) ? true : false;
		cmp_action(&index, RESUME, QUIT, c, 's', 'w');

		return pause_messege(index);
}


short main_menu(int index)
{
		int actual_page = PAGE1, actual_difficulty = EASY;
		int actual_score_tab_option = MENU, actual_score_tab = EASY;
		char _home[256];
		printf_menu();
		switch(index) {
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
		int c = 0;
		while ( c != 10 && c != 's' && c != 'w') c = getch();
		if (c == 10) {
				switch(index) {
				case START_GAME:
						return start_game_menu(actual_difficulty);
						break;
				case SCORE_TAB:
						score_tab_menu(&actual_score_tab_option, &actual_score_tab);
						if(actual_score_tab_option == CLEAN) {
								strcpy(_home, getenv("HOME"));
								strcat(_home, "/.bttConfig/btt");
								switch(actual_score_tab) {
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
						history(actual_page);
						break;
				case TUTORIAL:
						tutorial();
						break;
				case EXIT:
						exit(0);
						break;
				}
		}
		cmp_action(&index, START_GAME, EXIT, c, 's', 'w');

		return main_menu(index);
}


short select_player_menu(int index)
{
		printf_menu();
		printf("\t\t\t\tSelect a Player\n\n");
		switch(index) {
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

		int c = 0;
		while ( c != 10 && c != 's' && c != 'w') c = getch();

		if (c == 10)
				return (index == FIRST) ? '*' : (index == SECOND) ? '~' : '+';
		cmp_action(&index, FIRST, THIRD, c, 's', 'w');

		return select_player_menu(index);
}

short menu()
{
		return main_menu(START_GAME);
}

short select_player()
{
		return select_player_menu(FIRST);
}
