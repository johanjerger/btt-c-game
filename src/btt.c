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
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include "include/types.h"
#include "include/menu_enums.h"
#include "include/function.h"
#include "include/moves.h"
#include "include/verify.h"
#include "include/cheats.h"
#include "include/generate.h"
#include "include/error.h"
#include "include/menu.h"
#include "include/game_loop_function.h"


int game(block_arr area, int difficult, int * level, char player_char)
{
		short pause_option = RESUME, quit = 0;
		short key, i;
		int actual_position = A/2, actual_row = 1;
		int cnt_shots[AREA_HEIGHT], cnt_enemies[AREA_HEIGHT];
		int total_score = 0, num = 5;
		int handicap = 0, direction = 0;
		int is_cheat = 0, is_fb = 0, time_sleep = 0;
		int enem_level = 100, e_l = 100, time = 125;
		char cheat[CH];
		fireball ball;

		for(i = 0; i < CH - 1; i++) cheat[i] = ' ';
		cheat[CH-1]= '\0';

		for (i = 0; i != AREA_HEIGHT; i++)
		{
				cnt_shots[i] = 0;
				cnt_enemies[i] = 0;
		}

		// Some variables in base of the selected difficult for the game.
		int difficult_shots_penalties[] = {0, 2, 4, 6, 10};
		int enemies_numbers[] = {1, 5, 10, 15, 8};                             // I dont know what it is :/

		int difficult_shots_penalty = difficult_shots_penalties[difficult];
		int enem_number = enemies_numbers[difficult];

		// handicap = Total amount of bullet per level
		handicap = MAX_SHOTS_PER_ROW - difficult_shots_penalty;
		bullet shots[AREA_HEIGHT][handicap];
		enemies enem[AREA_HEIGHT][MC];

		// Special area, only for an easy control of the low level verification.
		block null_area;
		null_area.pos = -1;

		area[actual_row][actual_position].c = player_char;

		draw(area);
		printf_footbar(handicap, cnt_shots, actual_row, total_score, level);
		printf("press 't' for the tutorial or 'q' for exit\n");

		while(true)
		{
				key = kbhit();
				if(key)
				{
						is_cheat = verify_cheat(cheat, key);
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
								direction = 1;
								horizontal_move(direction, area, actual_row, &actual_position, player_char);
								break;
						case 'a':
								direction = 0;
								horizontal_move(direction, area, actual_row, &actual_position, player_char);
								break;
						case 'w':
								if(actual_row == 1)
								{
										jump(area, &actual_position, direction, player_char, 0);

										for(i = 1; i < AREA_HEIGHT; i++)
										{
												move_operations(area[i], shots[i], enem[i], &ball, &(cnt_shots[i]), &(cnt_enemies[i]), &is_fb, i);
												generate_enemies_control(area[i], enem[i], &(cnt_enemies[i]), &num, &enem_level,
												                         &e_l, &time, level, enem_number, &time_sleep, area);
												total_score += verify_shots(area[i], enem[i], shots[i], &(cnt_enemies[i]), &(cnt_shots[i]), handicap);
												fireball_control(&is_fb, i, &total_score, area[i], area[i-1], area[i+1],
												                 enem[i], enem[i-1], enem[i+1], &ball, &(cnt_enemies[i]),
												                 &(cnt_enemies[i-1]), &(cnt_enemies[i+1]), &null_area);
										}
										draw(area);
										printf_footbar(handicap, cnt_shots, actual_row, total_score, level);
										_nanosleep(time);

										jump(area, &actual_position, direction, player_char, 1);

										for(i = 1; i < AREA_HEIGHT; i++)
										{
												move_operations(area[i], shots[i], enem[i], &ball, &(cnt_shots[i]), &(cnt_enemies[i]), &is_fb, i);
												generate_enemies_control(area[i], enem[i], &(cnt_enemies[i]), &num, &enem_level,
												                         &e_l, &time, level, enem_number, &time_sleep, area);
												total_score += verify_shots(area[i], enem[i], shots[i], &(cnt_enemies[i]), &(cnt_shots[i]), handicap);
												fireball_control(&is_fb, i, &total_score, area[i], area[i-1], area[i+1],
												                 enem[i], enem[i-1], enem[i+1], &ball, &(cnt_enemies[i]),
												                 &(cnt_enemies[i-1]), &(cnt_enemies[i+1]), &null_area);
										}
										draw(area);
										printf_footbar(handicap, cnt_shots, actual_row, total_score, level);
										_nanosleep(time);

										jump(area, &actual_position, direction, player_char, 2);
								} else {
										area[actual_row][actual_position].c = ' ';
										actual_row--;
										area[actual_row][actual_position].c = player_char;
								}
								break;
						case 's':
								if(actual_row < AREA_HEIGHT-1)
								{
										area[actual_row][actual_position].c = ' ';
										actual_row++;
										area[actual_row][actual_position].c = player_char;
								}
								break;
						case 'k':
								generate_shots(area[actual_row], &(cnt_shots[actual_row]), shots[actual_row], actual_position, handicap, direction);
								break;
						case 'p':
								if (pause_messege(pause_option)) return total_score;
						}
				}


				if(!is_cheat)
				{
						for(i = 1; i < AREA_HEIGHT; i++)
						{
								move_operations(area[i], shots[i], enem[i], &ball, &(cnt_shots[i]), &(cnt_enemies[i]), &is_fb, i);

								generate_enemies_control(area[i], enem[i], &(cnt_enemies[i]), &num, &enem_level,
								                         &e_l, &time, level, enem_number, &time_sleep, area);

								total_score += verify_shots(area[i], enem[i], shots[i], &(cnt_enemies[i]), &(cnt_shots[i]), handicap);
								fireball_control(&is_fb, i, &total_score, area[i], area[i-1], area[i+1],
								                 enem[i], enem[i-1], enem[i+1], &ball, &(cnt_enemies[i]),
								                 &(cnt_enemies[i-1]), &(cnt_enemies[i+1]), &null_area);

								if(actual_row == i)
								{
										quit = verify_player(enem[i], area[i], actual_position, cnt_enemies[i]);
										if (quit) return total_score;
								}
						}
				} else {
						switch(is_cheat)
						{
						case 1:
								cheat_one(area[actual_row], &(cnt_enemies[actual_row]), &(cnt_shots[actual_row]), actual_position, player_char);
								break;
						case 2:
								if(!is_fb)
								{
										cheat_two(area[actual_row], &ball, actual_position, direction);
										is_fb = actual_row;
								}
						}
						is_cheat = 0;
				}

				draw(area);
				printf_footbar(handicap, cnt_shots, actual_row, total_score, level);
				_nanosleep(time);
		}
}
