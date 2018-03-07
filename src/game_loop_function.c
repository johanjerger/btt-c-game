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

void
printf_footbar(int handicap, int * cnt_shots, int row, int total_score, int * level)
{
		printf("\n\n\t" BLUE "Remaining shots:" RESET " %d\t\t\t" BLUE "Points:"
		       RESET " %d\n\t\t\t\t\t\t" BLUE "Level:" RESET " %d\n" RESET,
		       handicap - cnt_shots[row], total_score, *level);
}

void
level_up_messege(block_arr area)
{
		area[AREA_HEIGHT/2][(A/2)-3].c = 'L';
		area[AREA_HEIGHT/2][(A/2)-2].c = 'E';
		area[AREA_HEIGHT/2][(A/2)-1].c = 'V';
		area[AREA_HEIGHT/2][(A/2)].c = 'E';
		area[AREA_HEIGHT/2][(A/2)+1].c = 'L';
		area[AREA_HEIGHT/2][(A/2)+2].c = ' ';
		area[AREA_HEIGHT/2][(A/2)+3].c = 'U';
		area[AREA_HEIGHT/2][(A/2)+4].c = 'P';
}


void
horizontal_move(int direction, block_arr area, int row, int * pos, int player)
{
		int cmp_value = (direction) ? A - 2 : 1;
		int movement = (direction) ? 1 : -1;
		if(area[row][*pos].pos != cmp_value)
		{
				area[row][*pos].c = ' ';
				(*pos) += movement;
				area[row][*pos].c = player;
		}
}

void
move_operations(block * area, bullet * shots, enemies * local_enemies,
                fireball * ball, int * amount_of_shots,
                int * amount_of_enemies, int * is_fireball, int i)
{
		if(*is_fireball == i && !ball->is_imp)
		    move_fireball(area, ball, is_fireball);
		move_shots(area, shots, amount_of_shots);
		move_enemies(area, local_enemies, amount_of_enemies);
}


void
generate_enemies_control(block * area, enemies * local_enemies, int  * amount_of_enemies,
                         int * enemies_time_appearance,
                         int * time, int * level, int enemies_number,
                         int * time_sleep, block_arr big_area)
{
		if (*time_sleep)
		{
				(*time_sleep)--;
				if (*time_sleep == 500) level_up_messege(big_area);
				return;
		}
		generate_enemies(area, local_enemies, amount_of_enemies, enemies_time_appearance,
		                 time, level,enemies_number, time_sleep);
}


void
fireball_control(int * is_fb, int i, int * total_score, block_arr area,
	               enemies enem[10][10], fireball * ball, int amount_of_enemies[10])
{
		if (*is_fb == i)
			  *total_score += verify_fireball(i, area, enem, ball, amount_of_enemies, is_fb);
}
