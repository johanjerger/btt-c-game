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

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "include/types.h"
#include "include/delete.h"

bool
verify_collision(int character_position, int possible_collision)
{
		bool collision = false;
		collision |= character_position == possible_collision - 1;                                                                             // left collision
		collision |= character_position == possible_collision;                                                                             // center collision
		collision |= character_position == possible_collision + 1;                                                                             // right collision
		return collision;
}

short
cmp_fireball(block * area, enemies * enem, fireball * ball, int * cnt_enem)
{
    int points = 0;
    for(int i = 0; i != *cnt_enem; i++) {
        if (verify_collision(enem[i].pos, ball->pos))
        {
            points += 100;
            area[enem[i].pos].c = 'x';
            delete_enemy(enem, cnt_enem, i--);
        }
    }
    return points;
}

short
verify_shots(block * area, enemies * enem, bullet * shots, int * cnt_enem,
             int * cnt_shots)
{
		short points = 0;
    for(int i = 0; i != *cnt_enem; i++) {
				for(int j = 0; j != *cnt_shots; j++) {
						if (verify_collision(enem[i].pos, shots[j].pos))
						{
								points += 100;
                area[shots[j].pos].c = ' ';
                delete_shot(shots, cnt_shots, j);
                area[enem[i].pos].c = ' ';
                delete_enemy(enem, cnt_enem, i--);
                break;
						}
				}
		}
		return points;
}


bool verify_player(enemies * enem, block * area, int act, int cnt_enem)
{
		bool kill = false;
		for(int i = 0; i != cnt_enem; i++)
		{
				int movement = (enem[i].der) ? 1 : -1;
				kill |= enem[i].pos == area[act].pos;
				kill |= enem[i].pos == area[act + movement].pos;
		}
		return kill;
}

short verify_cheat(char * cheat, char key)
{
		cheat[CH-1] = key;
		for(int i = 0; i != CH - 1; i++) cheat[i] = cheat[i+1];
		cheat[CH-1] = '\0';
		if (!strcmp(cheat, "adkda")) return 1;
		if (!strcmp(cheat, "akdda") || !strcmp(cheat, "dkaad")) return 2;
		return 0;
}


short
verify_fireball(int position, block_arr area, enemies enem[10][10], fireball * ball,
								int cnt_enem[10], int * is_fireball)
{
		short points = 0;
		int low_position = position + 1;
		int top_position = position - 1;
		if(ball->mod == 0)
		{
				for(int i = 0; i < cnt_enem[position]; i++)
				{
						if (verify_collision(enem[position][i].pos, ball->pos))
						{
								area[position][ball->pos].c = ' ';
								ball->is_imp = true;
								ball->mod = 1;
								area[position][enem[position][i].pos].c = 'x';
								ball->pos = enem[position][i].pos;
								points += 150;
                delete_enemy(enem[position], &(cnt_enem[position]), i--);
								break;
						}
				}
		} else if (ball->mod == 1) {
				ball->mod = 2;
				area[position][ball->pos].c = 'x';
				area[position][ball->pos-1].c = 'x';
				area[position][ball->pos+1].c = 'x';
				area[top_position][ball->pos].c = 'x';
				area[top_position][ball->pos+1].c = 'x';
				area[top_position][ball->pos-1].c = 'x';
				if (low_position != AREA_HEIGHT - 2) {
						area[low_position][ball->pos].c = 'x';
						area[low_position][ball->pos+1].c = 'x';
						area[low_position][ball->pos-1].c = 'x';
				}
				points += cmp_fireball(area[position], enem[position], ball, &(cnt_enem[position]));
				points += cmp_fireball(area[top_position], enem[top_position], ball, &(cnt_enem[top_position]));
				if(low_position != AREA_HEIGHT - 2) {
						points += cmp_fireball(area[low_position], enem[low_position], ball, &(cnt_enem[low_position]));
				}

		} else if(ball->mod == 2) {
				ball->mod = 3;
				area[position][ball->pos].c = ' ';

				points += cmp_fireball(area[position], enem[position], ball, &(cnt_enem[position]));
				points += cmp_fireball(area[top_position], enem[top_position], ball, &(cnt_enem[top_position]));
				if(low_position != AREA_HEIGHT - 2) {
						points += cmp_fireball(area[low_position], enem[low_position], ball, &(cnt_enem[low_position]));
				}

		} else if(ball->mod == 3) {
				ball->mod = 0;
				ball->is_imp = 0;
				area[position][ball->pos-1].c = ' ';
				area[position][ball->pos+1].c = ' ';
				area[top_position][ball->pos].c = ' ';
				area[top_position][ball->pos+1].c = ' ';
				area[top_position][ball->pos-1].c = ' ';
				if(low_position != AREA_HEIGHT - 2) {
						area[low_position][ball->pos].c = ' ';
						area[low_position][ball->pos+1].c = ' ';
						area[low_position][ball->pos-1].c = ' ';
				}
				*is_fireball = 0;
		}

		return points;
}
