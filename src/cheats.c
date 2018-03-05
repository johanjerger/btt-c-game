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
#include <stdbool.h>
#include "include/types.h"

void
cheat_one(block * area, int * cnt_enem, int * cnt_shots, int act, char pj)
{
		*cnt_enem = 0;
		*cnt_shots = 0;
		for(int i = 1; i != A - 1; i++) area[i].c = ' ';
		area[act].c = pj;
}


void
cheat_two(block * area, fireball * ball, int act, int der)
{
		ball->is_imp = false;
		ball->mod = 0;
		ball->pos = (der) ? act + 1 : act - 1;
		ball->der = der;
		area[ball->pos].c = 'x';
}
