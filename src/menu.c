/***************************************************************************
*
*				 «©Copyright 2016-2018 Juan Cruz Ocampos»
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
#include "include/game_texts.h"

void printf_menu()
{
		clear();
		printf(BTT_TITLE RESET);
}


void footbar_menu()
{
		printf("\tUse the 'w' & 's' to switch the select option - press " GREEN
					 "ENTER" RESET " to select\n\t\t\t\t\t\t\t  " CYAN "Version %s\n\n"
					 RESET, VERSION);
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

void print_options(const char * options[], int index, int amount)
{
		for (int i = 0; i < amount; i++)
		{
				if (i == index)
						printf(YELLOW "\t\t\t\t %s \n" RESET, options[i]);
				else
						printf("\t\t\t\t %s \n", options[i]);
		}
}

int history(int index)
{
		int pages = (int) max_score() /  100;
		if(pages > 9) pages = 9;
		clear();
		printf_menu();
		printf(histories[index]);
		printf("\n\tUse the 'a' & 'd' to switch the differents history pages\t page %d/%d\n", index + 1, pages + 1);
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

		int opt_size = sizeof(difficulties) / sizeof(difficulties[0]);
		print_options(difficulties, index, opt_size);
		printf("\n\n");
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
		strcat(_home, file_names[*actual_score_tab]);
		score_tab(_home, *actual_score_tab);
		printf("\n");

		int opt_size = sizeof(score_table_options) / sizeof(score_table_options[0]);
		print_options(score_table_options, *actual_score_tab_option, opt_size);

		printf("\n\n");
		printf("\tUse the 'a' & 'd' to switch the differents score tables\n");
		footbar_menu();
		int c = 0;
		while (c != 10 && c != 's' && c != 'w' && c != 'a' && c != 'd') c = getch();
		if (c == 10) return 0;
		cmp_action(actual_score_tab_option, MENU, CLEAN, c, 's', 'w');
		cmp_action(actual_score_tab, EASY, HOPELESS, c, 'd', 'a');

		return score_tab_menu(actual_score_tab_option, actual_score_tab);
}


bool pause_messege(int index)
{
		printf_menu();
		printf("\n\t\t\t\t" BLUE "   PAUSE" RESET "\n\n");
		int opt_size = sizeof(pause_options) / sizeof(pause_options[0]);
		print_options(pause_options, index, opt_size);
		printf("\n\n\n");
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
		int opt_size = sizeof(option_names) / sizeof(option_names[0]);
		print_options(option_names, index, opt_size);
		printf("\n\n\n");

		footbar_menu();
		int c = 0;
		while ( c != 10 && c != 's' && c != 'w') c = getch();
		if (c == 10) {
				switch(index) {
				case START_GAME:
						return start_game_menu(actual_difficulty);
						break;
				case SCORE_TAB:
						score_tab_menu(&actual_score_tab_option, &actual_score_tab); // TODO loop when you clean a score table
						if(actual_score_tab_option == CLEAN) {
								strcpy(_home, getenv("HOME"));
								strcat(_home, "/.bttConfig/btt");
								strcat(_home, file_names[actual_score_tab]);
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
				}
		}
		cmp_action(&index, START_GAME, EXIT, c, 's', 'w');

		return main_menu(index);
}


short select_player_menu(int index)
{
		printf_menu();
		printf("\t\t\t\tSelect a Player\n\n");
		int opt_size = sizeof(players) / sizeof(players[0]);
		print_options(players, index, opt_size);
		printf("\n\n\n");
		footbar_menu();
		int c = 0;
		while ( c != 10 && c != 's' && c != 'w') c = getch();
		if (c == 10) return (index == FIRST) ? '*' : (index == SECOND) ? '~' : '+';
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

bool pause_game()
{
		return pause_messege(RESUME);
}
