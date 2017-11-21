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
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include "include/types.h"
#include "include/function.h"
#include "include/moves.h"
#include "include/verify.h"
#include "include/cheats.h"
#include "include/generate.h"
#include "include/error.h"
#include "include/menu.h"
#include "include/game_loop_function.h"


	int game(block_arr area, int * difficulty, int * level, char player_char)
	{
		short pause_option = RESUME, quit = 0;
		short key, i;
		int actual_position = A/2, actual_row = 1;
		int amount_of_shots[L], amount_of_enemies[L];
		int total_score = 0, num = 5, dif_n = 0, enem_n = 0;
		int handicap = 0, direction = 0;
		int is_cheat = 0, cheat_type, is_fb = 0, time_sleep = 0;
		int enem_level = 100, e_l = 100, time = 125;
		char cheat[CH];
		fireball ball;

		//	The party star after the player and difficulty selection.


		for(i = 0; i < CH - 1; i++)
		{
			/*
				This block initialize the char array for verify if the player
				make some cool "cheat".
			*/
			cheat[i] = ' ';
		}
		cheat[CH-1]= '\0';

		for(i = 0; i < L; i++)
		{
			// Another variable initialization...
			amount_of_shots[i] = 0;
			amount_of_enemies[i] = 0;
		}

		switch(*difficulty)
		{
			/*
				Some variables in base of the selected difficulty for the
				game.
			*/
		case EASY:
			dif_n = 0; enem_n = 1;
			break;
		case NORMAL:
			dif_n = 2; enem_n = 5;
			break;
		case HARD:
			dif_n = 4; enem_n = 10;
			break;
		case VERY_HARD:
			dif_n = 6; enem_n = 15;
			break;
		case HOPELESS:
			dif_n = 10; enem_n = 8;
			break;
		}

		// handicap = Total amount of bullet per level
		handicap = C - dif_n;
		bullet shots[L][handicap];
		enemies enem[L][MC];

		// Special area, only for an easy control of the low level verification.
		block null_area;
		null_area.pos = -1;

		area[actual_row][actual_position].c = player_char;

		draw(area);
		printf_footbar(handicap, amount_of_shots, actual_row, total_score, level);
		printf("press 't' for the tutorial or 'q' for exit\n");

		// The basic <while true> loop begin.
		do
		{
			// The key variable store the key that you press.
			if((key = kbhit()))
			{
				// The tolower is only for a clear control of the key...
				key = tolower(key);
				switch(key)
				{
					/*
						The 'd' and 'a' cases controls the horiontal move of
						of the player.

						The 'w' case only control the up movement, but if the
						player are in the first level the case make the "jump"
						animation (in other words, hardcoded movements).

						The 's' case controls the down movement only if you are
						not in the last level.

						The 'k' case controls and generate a shoot, adding this
						in the shots matrix.

						All the cases mentioned before verify the cheat array
						and turn a bit if there's a cheat in It.

						For last, the 'p' case control the pause, where you can
						quit the game and go back the main manu.
					*/
				case 'd':
					is_cheat = verify_cheat(cheat, &cheat_type, key);
					horizontal_move(A-2, 1, 1, area, actual_row, &actual_position, player_char, &direction);
					break;
				case 'a':
					is_cheat = verify_cheat(cheat, &cheat_type, key);
					horizontal_move(1, -1, 0, area, actual_row, &actual_position, player_char, &direction);
					break;
				case 'w':
					is_cheat = verify_cheat(cheat, &cheat_type, key);
					if(actual_row == 1)
					{
						jump(area, &actual_position, direction, player_char, 0);

						for(i = 1; i < L; i++)
						{
							move_operations(area[i], shots[i], enem[i], &ball, &(amount_of_shots[i]), &(amount_of_enemies[i]), &is_fb, i);
							generate_enemies_control(area[i], enem[i], &(amount_of_enemies[i]), &num, &enem_level,
													 &e_l, &time, level, enem_n, &time_sleep, area);
							total_score += verify_shots(area[i], enem[i], shots[i], &(amount_of_enemies[i]), &(amount_of_shots[i]), handicap);
							fireball_control(&is_fb, i, &total_score, area[i], area[i-1], area[i+1],
										 	 enem[i], enem[i-1], enem[i+1], &ball, &(amount_of_enemies[i]),
										 	 &(amount_of_enemies[i-1]), &(amount_of_enemies[i+1]), &null_area);
						}
						draw(area);
						printf_footbar(handicap, amount_of_shots, actual_row, total_score, level);
						_nanosleep(time);

						jump(area, &actual_position, direction, player_char, 1);

						for(i = 1; i < L; i++)
						{
							move_operations(area[i], shots[i], enem[i], &ball, &(amount_of_shots[i]), &(amount_of_enemies[i]), &is_fb, i);
							generate_enemies_control(area[i], enem[i], &(amount_of_enemies[i]), &num, &enem_level,
													 &e_l, &time, level, enem_n, &time_sleep, area);
							total_score += verify_shots(area[i], enem[i], shots[i], &(amount_of_enemies[i]), &(amount_of_shots[i]), handicap);
							fireball_control(&is_fb, i, &total_score, area[i], area[i-1], area[i+1],
										 	 enem[i], enem[i-1], enem[i+1], &ball, &(amount_of_enemies[i]),
										 	 &(amount_of_enemies[i-1]), &(amount_of_enemies[i+1]), &null_area);
						}
						draw(area);
						printf_footbar(handicap, amount_of_shots, actual_row, total_score, level);
						_nanosleep(time);

						jump(area, &actual_position, direction, player_char, 2);
					} else {
						area[actual_row][actual_position].c = ' ';
						actual_row--;
						area[actual_row][actual_position].c = player_char;
					}
					break;
				case 's':
					is_cheat = verify_cheat(cheat, &cheat_type, key);
					if(actual_row < L-1)
					{
						area[actual_row][actual_position].c = ' ';
						actual_row++;
						area[actual_row][actual_position].c = player_char;
					}
					break;
				case 'k':
					is_cheat = verify_cheat(cheat, &cheat_type, key);
					generate_shots(area[actual_row], &(amount_of_shots[actual_row]), shots[actual_row], actual_position, handicap, direction);
					break;
				case 'p':
					pause_messege(pause_option, &quit);
					if (quit) return total_score;
					break;
				}
			}


			if(!is_cheat)
			{
				for(i = 1; i < L; i++)
				{
					move_operations(area[i], shots[i], enem[i], &ball, &(amount_of_shots[i]), &(amount_of_enemies[i]), &is_fb, i);

					generate_enemies_control(area[i], enem[i], &(amount_of_enemies[i]), &num, &enem_level,
											 &e_l, &time, level, enem_n, &time_sleep, area);

					total_score += verify_shots(area[i], enem[i], shots[i], &(amount_of_enemies[i]), &(amount_of_shots[i]), handicap);
					fireball_control(&is_fb, i, &total_score, area[i], area[i-1], area[i+1],
									 enem[i], enem[i-1], enem[i+1], &ball, &(amount_of_enemies[i]),
									 &(amount_of_enemies[i-1]), &(amount_of_enemies[i+1]), &null_area);

					if(actual_row == i)
					{
						quit = verify_player(enem[i], area[i], actual_position, amount_of_enemies[i]);
						if (quit) return total_score;
						continue;
					}
				}
			} else {
				switch(cheat_type)
				{
				case 1:
					cheat_one(area[actual_row], &(amount_of_enemies[actual_row]), &(amount_of_shots[actual_row]), actual_position, player_char);
					break;
				case 2:
					if(!is_fb)
					{
						cheat_two(area[actual_row], &ball, actual_position, direction);
						is_fb = actual_row;
					}
					break;
				}
				is_cheat = 0;
			}

			draw(area);
			printf_footbar(handicap, amount_of_shots, actual_row, total_score, level);
			_nanosleep(time);
		} while(1);

		return total_score;
	}
