/***************************************************************************
*
*				 «©Copyright 2016-2018 Juan Cruz Ocampos»
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
#include "include/delete.h"

void move_shots(block * area, bullet * shots, int * cnt_shots)
{
		for (int i = 0; i != *cnt_shots; i++)
		{
				area[shots[i].pos].c = ' ';
				shots[i].pos += (shots[i].der) ? 1 : -1;
				int cmp_value = (shots[i].der) ? A - 1 : 0;
				if (shots[i].pos != cmp_value) area[shots[i].pos].c = '-';
				else delete_shot(shots, cnt_shots, i--);
		}
}

void move_enemies(block * area, enemies * enem, int * cnt_enemies)
{
		for (int i = 0; i < *cnt_enemies; i++)
		{
				area[enem[i].pos].c = ' ';
				enem[i].pos += (enem[i].der) ? 1 : -1;
				int cmp_value = (enem[i].der) ? A - 1 : 0;
				if (enem[i].pos != cmp_value) area[enem[i].pos].c = '#';
				else delete_enemy(enem, cnt_enemies, i--);
		}
}

void move_fireball(block * area, fireball * ball, int * is_fireball)
{
		area[ball->pos].c = ' ';
		ball->pos += (ball->der) ? 1 : -1;
		int cmp_value = (ball->der) ? A - 2 : 1;
		if (ball->pos != cmp_value) area[ball->pos].c = 'x';
		else *is_fireball = 0;
}

void jump(block_arr area, int * act, int der, int pj, int mod)
{
		int cmp_value, movement;
		cmp_value = (der) ? A - 2 : 1;
		movement = (der) ? 1 : -1;
		switch (mod)
		{
		case 0:
				if (area[1][*act].pos != cmp_value)
				{
						area[1][*act].c = ' ';
						*act += movement;
						area[0][*act].c = pj;
				}
				break;
		case 1:
				if (area[0][*act].pos != cmp_value)
				{
						area[0][*act].c = ' ';
						*act += movement;
						area[0][*act].c = pj;
				}
				break;
		case 2:
				if (area[1][*act].pos != cmp_value)
				{
						area[0][*act].c = ' ';
						*act += movement;
						area[1][*act].c = pj;
				} else {
						area[0][*act].c = ' ';
						area[1][*act].c = pj;
				}
		}
}
