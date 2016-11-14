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
#include <errno.h>
#include "include/types.h"
#include "include/error.h"
#include "include/function.h"
#include "include/btt.h"
#include "include/menu.h"
#include "include/score_table.h"


	int main()
	{
		int i, game_difficulty_level, end_level, result;
		int actual_option = START_GAME, actual_player = FIRST;
		char player_char;
		block_arr area;

	  	/* 
	  		We initialice every single level
	  		of the matrix area.
	  	*/

		for(i=0; i < L; i++){
			initialize_area(area[i]);			
		}

		// Can We call this the "Menu Loop"?

		do{
			game_difficulty_level = menu(actual_option);

			if(game_difficulty_level != 'q'){
				end_level = 1; 
				result = 0;
				
				player_char = select_player(actual_player);
				result = game(area, &game_difficulty_level, &end_level, player_char);
				
				clear();
				if(result > 15000){
					printf(RED "\t\t\tGAME OVER!\n" RESET "\t\t\tScore: %d  :D\n\n", result);
				} else if (result > 10000){
					printf(RED "\t\t\tGAME OVER!\n" RESET "\t\t\tScore: %d  :)\n\n", result);
				} else if(result > 5000){
					printf(RED "\t\t\tGAME OVER!\n" RESET "\t\t\tScore: %d  :|\n\n", result);
				} else {
					printf(RED "\t\t\tGAME OVER!\n" RESET "\t\t\tScore: %d  :(\n\n", result);
				}
				
				_nanosleep(2000);
				
				is_high_score(result, end_level, game_difficulty_level);
				
				// We clean the area for another game.

				for(i=0; i < L; i++){
					initialize_area(area[i]);
				}
			}

		} while((game_difficulty_level != 'q'));

		clear();

		return 0;
	}
