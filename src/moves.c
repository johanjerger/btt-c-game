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
#include "include/types.h"

void delete_shot(bullet * shots, int * cnt_shots, int position)
{
		for(int j = position; j < *cnt_shots; j++)
		{
				shots[j].pos = shots[j+1].pos;
				shots[j].der = shots[j+1].der;
		}
		(*cnt_shots)--;
}

void move_shots(block * area, bullet * shots, int * cnt_shots)
{
		int k = 0, cmp_value;

		for(int i = 0; i != *cnt_shots; i++)
		{
				area[shots[k].pos].c = ' ';
				if(shots[k].der) {
						shots[k].pos++;
						cmp_value = A - 1;
				} else {
						shots[k].pos--;
						cmp_value = 0;
				}
				if(shots[k].pos != cmp_value) area[shots[k++].pos].c = '-';
				else delete_shot(shots, cnt_shots, k);
		}
}

void delete_enemy(enemies * enem, int * cnt_enem, int position)
{
		for(int j = position; j < *cnt_enem; j++)
		{
				enem[j].pos = enem[j+1].pos;
				enem[j].der = enem[j+1].der;
		}
		(*cnt_enem)--;
}

void move_enemies(block * area, enemies * enem, int * cnt_enem)
{
		int k = 0, cmp_value;

		for(int i = 0; i < *cnt_enem; i++)
		{
				area[enem[k].pos].c = ' ';
				if(enem[k].der) {
						enem[k].pos++;
						cmp_value = A - 1;
				} else {
						enem[k].pos--;
						cmp_value = 0;
				}
				if(enem[k].pos != cmp_value) area[enem[k++].pos].c = '#';
				else delete_enemy(enem, cnt_enem, k);
		}
}

void move_fireball(block * area, fireball * ball, int * is_fireball)
{
		if(!ball->is_imp) {
				int cmp_value;
				area[ball->pos].c = ' ';

				if(ball->der) {
						ball->pos++;
						cmp_value = A - 2;
				} else {
						ball->pos--;
						cmp_value = 1;
				}

				if(ball->pos != cmp_value) area[ball->pos].c = 'x';
				else *is_fireball = 0;
		}
}

void jump(block_arr area, int * act, int der, int pj, int mod)
{
		int cmp_value, movement;
		switch (mod) {
		case 0:
				cmp_value = (der) ? A - 2 : 1;
				movement = (der) ? 1 : -1;
				if (area[1][*act].pos != cmp_value)
				{
						area[1][*act].c = ' ';
						*act += movement;
						area[0][*act].c = pj;
				}
				break;
		case 1:
				cmp_value = (der) ? A - 2 : 1;
				movement = (der) ? 1 : -1;
				if (area[0][*act].pos != cmp_value)
				{
						area[0][*act].c = ' ';
						*act += movement;
						area[0][*act].c = pj;
				}
				break;
		case 2:
				cmp_value = (der) ? A - 2 : 1;
				movement = (der) ? 1 : 0;
				if (area[1][*act].pos != cmp_value)
				{
						area[0][*act].c = ' ';
						*act += movement;
						area[1][*act].c = pj;
				}
				break;
		default:
				cmp_value = (der) ? A - 2 : 1;
				movement = (der) ? -1 : 0;
				if (area[1][*act].pos != cmp_value)
				{
						area[0][*act].c = ' ';
						*act += movement;
						area[1][*act].c = pj;
				}
				break;
		}
}
