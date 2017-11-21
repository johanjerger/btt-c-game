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


	int generate_enemies(block * area, enemies * enem, int * cnt_enem,
						 int * num, int * enem_level, int * e_l, int * time,
						 int * level, int enemy_num, int * time_sleep)
  	{
		int side;
		int success = 0;

		if(!*num){
			//num = rand() % (n - m + 1) + m   ---  [M, N]
			*num = rand() % (MT - enemy_num) + 1;
			if(*cnt_enem < MC){
				side = rand() % (21) - 10;
				if(side >= 0){
					enem[*cnt_enem].pos = 1;
					enem[*cnt_enem].der = 1;
					if((area[enem[*cnt_enem].pos+1].c) != '#'){
						success = 1;
						area[enem[*cnt_enem].pos].c = '#';
					}
				} else {
					enem[*cnt_enem].pos = A - 2;
					enem[*cnt_enem].der = 0;
					if((area[enem[*cnt_enem].pos-1].c) != '#'){
						success = 1;
						area[enem[*cnt_enem].pos].c = '#';
					}
				}
				if(success){
					(*enem_level)--;
					if(!*enem_level){
						*time -= 15;
						*time_sleep = 1000;
						(*level)++;
						*enem_level = (*e_l) * (*level);
					}
					(*cnt_enem)++;
				}
			}
		} else {
			(*num)--;
		}

		return 0;
	}


	int generate_shots(block * area, int * c_shots, bullet * shots,
					   int act, int handicap, int der)
	{
		if((area[act+2].c != '-') && (area[act-2].c != '-')){
			if(*c_shots < handicap){
				shots[*c_shots].der = der;
				if(shots[*c_shots].der){
					shots[*c_shots].pos = act + 1;
					area[shots[*c_shots].pos].c = '-';
				} else {
					shots[*c_shots].pos = act - 1;
					area[shots[*c_shots].pos].c = '-';
				}
				(*c_shots)++;
			}
		}
		return 0;
	}
