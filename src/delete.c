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

void delete_shot(bullet * shots, int * cnt_shots, int position)
{
		for (int i = position; i < *cnt_shots; i++)
		{
				shots[i].pos = shots[i+1].pos;
				shots[i].der = shots[i+1].der;
		}
		(*cnt_shots)--;
}

void delete_enemy(enemies * enem, int * cnt_enemies, int position)
{
		for (int i = position; i < *cnt_enemies; i++)
		{
				enem[i].pos = enem[i+1].pos;
				enem[i].der = enem[i+1].der;
		}
		(*cnt_enemies)--;
}
