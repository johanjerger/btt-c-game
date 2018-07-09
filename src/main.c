/***************************************************************************
*
*				 «©Copyright 2016-2018 Juan Cruz Ocampo»
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
#include <errno.h>
#include <time.h>
#include "include/types.h"
#include "include/error.h"
#include "include/function.h"
#include "include/btt.h"
#include "include/menu.h"
#include "include/score_table.h"


int
main (void)
{
		srand(time(NULL)); // random seeds
		while(true)
		{
				int difficult = menu();
				int end_level = 1;
				char player_char = select_player();

				int result = game(difficult, &end_level, player_char);

				clear();
				printf(RED "\t\t\tGAME OVER!\n" RESET "\t\t\tScore: %d\n\n", result);
				printf("\n\t\t\tpress " GREEN "ENTER" RESET "\n");

				// await for an Enter
				while((getch())!='\n');
				is_high_score(result, end_level, difficult);
		}
}
