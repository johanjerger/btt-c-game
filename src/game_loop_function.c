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
#include <ctype.h>
#include "include/types.h"
#include "include/moves.h"
#include "include/function.h"
#include "include/menu.h"
#include "include/generate.h"
#include "include/verify.h"

int printf_footbar(int handicap, int * amount_of_shots, int actual_row,
                   int total_score, int * level)
{
		printf("\n\n\t" BLUE "Remaining shots:" RESET " %d\t\t\t" BLUE "Points:" RESET " %d\n\t\t\t\t\t\t" BLUE "Level:" RESET " %d\n" RESET, handicap - amount_of_shots[actual_row], total_score, *level);

		return 0;
}

int level_up_messege(block_arr area)
{
		area[AREA_HEIGHT/2][(A/2)-3].c = 'L';
		area[AREA_HEIGHT/2][(A/2)-2].c = 'E';
		area[AREA_HEIGHT/2][(A/2)-1].c = 'V';
		area[AREA_HEIGHT/2][(A/2)].c = 'E';
		area[AREA_HEIGHT/2][(A/2)+1].c = 'L';
		area[AREA_HEIGHT/2][(A/2)+2].c = ' ';
		area[AREA_HEIGHT/2][(A/2)+3].c = 'U';
		area[AREA_HEIGHT/2][(A/2)+4].c = 'P';

		return 0;
}


int horizontal_move(int position, int modify_position, int new_direction,
                    block_arr area, int actual_row, int * actual_position,
                    int player_char, int * direction)
{
		if(area[actual_row][*actual_position].pos != position) {
				area[actual_row][*actual_position].c = ' ';
				(*actual_position) += modify_position;
				area[actual_row][*actual_position].c = player_char;
				*direction = new_direction;
		}

		return 0;
}


int move_operations(block * area, bullet * shots, enemies * local_enemies,
                    fireball * ball, int * amount_of_shots,
                    int * amount_of_enemies, int * is_fireball, int i)
{
		if(*is_fireball == i) {
				move_fireball(area, ball, is_fireball);
		}
		move_shots(area, shots, amount_of_shots);
		move_enemies(area, local_enemies, amount_of_enemies);

		return 0;
}


int generate_enemies_control(block * area, enemies * local_enemies, int  * amount_of_enemies,
                             int * enemies_time_appearance, int * enemies_per_level,
                             int * e_l, int * time, int * level, int enemies_number,
                             int * time_sleep, block_arr big_area)
{
		if(!*time_sleep) {
				generate_enemies(area, local_enemies, amount_of_enemies,
				                 enemies_time_appearance, enemies_per_level, e_l,
				                 time, level,enemies_number, time_sleep);
		} else {
				(*time_sleep)--;
				if(*time_sleep == 500) {
						level_up_messege(big_area);
				}
		}
		return 0;
}


int fireball_control(int * is_fb, int i, int * total_score,
                     block * area1, block * area2, block * area3,
                     enemies * enem1, enemies * enem2, enemies * enem3,
                     fireball * ball, int * amount_of_enemies1, int * amount_of_enemies2,
                     int * amount_of_enemies3, block * null_area)
{
		if(*is_fb == i) {
				if(i < (AREA_HEIGHT-1)) {
						(*total_score) += verify_fireball(area1, area2, area3, enem1, enem2, enem3, ball, amount_of_enemies1, amount_of_enemies2, amount_of_enemies3, is_fb);
				} else if(i == (AREA_HEIGHT-1)) {
						(*total_score) += verify_fireball(area1, area2, null_area, enem1, enem2, enem3, ball, amount_of_enemies1, amount_of_enemies2, amount_of_enemies3, is_fb);
				}
		}

		return 0;
}
