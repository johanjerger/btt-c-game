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


int
game (int difficult, int * level, char player_char)
{
		short key;
		int position = A/2, row = 1; // Player position
		int cnt_shots[AREA_HEIGHT], cnt_enemies[AREA_HEIGHT];
		int points = 0, num = 5;
		int handicap = 0, direction = 0;
		int is_cheat, is_fb = 0, time_sleep = 0;
		int time = 125;
		char cheat[CH];
		fireball ball;

		// Area initialization
		block_arr area;
		for (int i=0; i != AREA_HEIGHT; i++) initialize_area(area[i]);

		for(int i = 0; i < CH - 1; i++) cheat[i] = ' ';
		cheat[CH-1]= '\0';

		for (int i = 0; i != AREA_HEIGHT; i++)
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

		area[row][position].c = player_char;

		draw(area);
		printf_footbar(handicap, cnt_shots, row, points, level);
		printf("press 't' for the tutorial or 'q' for exit\n");

		while(true)
		{
				key = kbhit();
				if(key)
				{
						is_cheat = verify_cheat(cheat, key);
						switch(key)
						{
						case 'd':
								direction = 1;
								horizontal_move(direction, area, row, &position, player_char);
								break;
						case 'a':
								direction = 0;
								horizontal_move(direction, area, row, &position, player_char);
								break;
						case 'w':
								if(row == 1)
								{
										jump(area, &position, direction, player_char, 0);

										for(int i = 1; i < AREA_HEIGHT; i++)
										{
												move_operations(area[i], shots[i], enem[i], &ball, &(cnt_shots[i]), &(cnt_enemies[i]), &is_fb, i);
												generate_enemies_control(area[i], enem[i], &(cnt_enemies[i]), &num,
												                         &time, level, enem_number, &time_sleep, area);
												points += verify_shots(area[i], enem[i], shots[i], &(cnt_enemies[i]), &(cnt_shots[i]));
												fireball_control(&is_fb, i, &points, area, enem, &ball, cnt_enemies);
										}
										draw(area);
										printf_footbar(handicap, cnt_shots, row, points, level);
										_nanosleep(time);

										jump(area, &position, direction, player_char, 1);

										for(int i = 1; i < AREA_HEIGHT; i++)
										{
												move_operations(area[i], shots[i], enem[i], &ball, &(cnt_shots[i]), &(cnt_enemies[i]), &is_fb, i);
												generate_enemies_control(area[i], enem[i], &(cnt_enemies[i]), &num,
												                         &time, level, enem_number, &time_sleep, area);
												points += verify_shots(area[i], enem[i], shots[i], &(cnt_enemies[i]), &(cnt_shots[i]));
												fireball_control(&is_fb, i, &points, area, enem, &ball, cnt_enemies);
										}
										draw(area);
										printf_footbar(handicap, cnt_shots, row, points, level);
										_nanosleep(time);

										jump(area, &position, direction, player_char, 2);
								} else {
										area[row][position].c = ' ';
										row--;
										area[row][position].c = player_char;
								}
								break;
						case 's':
								if(row == AREA_HEIGHT-1) break;
								area[row++][position].c = ' ';
								area[row][position].c = player_char;
								break;
						case 'k':
								generate_shots(area[row], &(cnt_shots[row]), shots[row], position, handicap, direction);
								break;
						case 'p':
								if (pause_game()) return points;
						}
				}


				if(is_cheat)
				{
						switch(is_cheat)
						{
						case 1:
								cheat_one(area[row], &(cnt_enemies[row]), &(cnt_shots[row]), position, player_char);
								break;
						case 2:
								if(!is_fb)
								{
										cheat_two(area[row], &ball, position, direction);
										is_fb = row;
								}
						}
						is_cheat = 0;
				}

				for(int i = 1; i < AREA_HEIGHT; i++)
				{
						move_operations(area[i], shots[i], enem[i], &ball, &(cnt_shots[i]), &(cnt_enemies[i]), &is_fb, i);

						generate_enemies_control(area[i], enem[i], &(cnt_enemies[i]), &num,
																		 &time, level, enem_number, &time_sleep, area);

						points += verify_shots(area[i], enem[i], shots[i], &(cnt_enemies[i]), &(cnt_shots[i]));
						fireball_control(&is_fb, i, &points, area, enem, &ball, cnt_enemies);
				}
				if (verify_player(enem[row], area[row], position, cnt_enemies[row]))
						return points;

				draw(area);
				printf_footbar(handicap, cnt_shots, row, points, level);
				_nanosleep(time);
		}
}
