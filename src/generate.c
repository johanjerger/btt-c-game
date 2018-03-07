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

#include <stdlib.h>
#include <stdio.h>
#include "include/types.h"
#include "include/function.h"

int enemies_per_level = 100;

void generate_enemies(block * area, enemies * enem, int * cnt_enem,
                     int * num, int * time,
                     int * level, int enemy_num, int * time_sleep)
{
		if(!*num) {
				//num = rand() % (n - m + 1) + m   ---  [M, N]
				*num = rand() % (MT - enemy_num) + 1;
				if(*cnt_enem < MC) {
						int side = rand() % (21) - 10;
						enem[*cnt_enem].pos = (side >= 0) ? 1 : A - 2;
						enem[*cnt_enem].der = (side >= 0) ? 1 : 0;
            area[enem[(*cnt_enem)++].pos].c = '#';
						enemies_per_level--;
						if(!enemies_per_level) {
								*time -= 15;
								*time_sleep = 1000;
								(*level)++;
								enemies_per_level = 100 * (*level);
						}
				}
		} else (*num)--;
}


void generate_shots(block * area, int * cnt_shots, bullet * shots,
                   int act, int handicap, int der)
{
    int movement = (der) ? 1 : -1;
		if(area[act + movement].c != '-') {
				if(*cnt_shots < handicap) {
						shots[*cnt_shots].der = der;
            shots[*cnt_shots].pos = act + movement;
            area[shots[(*cnt_shots)++].pos].c = '-';
				}
		}
}
