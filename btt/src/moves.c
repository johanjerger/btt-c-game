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


	int move_shots(block * area, bullet * shots, int * cnt_shots)
	{
		int i, j, k = 0;

		for(i = 0; i < *cnt_shots; i++){
			if(shots[k].der){
				area[shots[k].pos].c = ' ';
				shots[k].pos++;
				if(shots[k].pos < A - 1){
						area[shots[k].pos].c = '-';
						k++;
				} else {
					for(j = k; j < *cnt_shots; j++){
						shots[j].pos = shots[j+1].pos;
						shots[j].der = shots[j+1].der;
					}
					(*cnt_shots)--;
				}
			} else {
				area[shots[k].pos].c = ' ';
				shots[k].pos--;
				if(shots[k].pos > 0){
					area[shots[k].pos].c = '-';
					k++;
				} else {
					for(j = k; j < *cnt_shots; j++){
						shots[j].pos = shots[j+1].pos;
						shots[j].der = shots[j+1].der;
					}
					k = i;
					(*cnt_shots)--;
				}
			}
		}

		return 0;
	}


	int move_enem(block * area, enemies * enem, int * cnt_enem)
	{
		int i, j, k = 0;

		for(i = 0; i < *cnt_enem; i++){
			if(enem[k].der){
				area[enem[k].pos].c = ' ';
				enem[k].pos++;
				if(enem[k].pos < A - 1){
					area[enem[k].pos].c = '#';
					k++;
				} else {
					for(j = k; j < *cnt_enem; j++){
						enem[j].pos = enem[j+1].pos;
						enem[j].der = enem[j+1].der;
					}
					k = i;
					(*cnt_enem)--;
				}
			} else {
				area[enem[k].pos].c = ' ';
				enem[k].pos--;
				if(enem[k].pos > 0){
					area[enem[k].pos].c = '#';
					k++;
				} else {
					for(j = k; j < *cnt_enem; j++){
						enem[j].pos = enem[j+1].pos;
						enem[j].der = enem[j+1].der;
					}
					k = i;
					(*cnt_enem)--;
				}
			}
		}

		return 0;
	}


	int move_fireball(block * area, fireball * ball, int * is_fireball)
	{
		if(!ball->is_imp){
			if(ball->der){
				area[ball->pos].c = ' ';
				ball->pos++;
				if(ball->pos < A - 2){
						area[ball->pos].c = 'x';
				} else {
					*is_fireball = 0;
				}
			} else {
				area[ball->pos].c = ' ';
				ball->pos--;
				if(ball->pos > 1){
					area[ball->pos].c = 'x';
				} else {
					*is_fireball = 0;
				}
			}
		}

		return *is_fireball;
	}


	int jump(block_arr area, int * act, int der, int pj, int mod)
	{
		if(mod == 0){
			if(der){
				if(area[1][*act].pos != A - 2){
					area[1][(*act)++].c = ' ';
					area[0][*act].c = pj;
				}
			} else {
				if(area[1][*act].pos != 1){
					area[1][(*act)--].c = ' ';
					area[0][*act].c = pj;
				}
			}
		} else if(mod == 1){
			if(der){
				if(area[0][*act].pos != A - 2){
					area[0][(*act)++].c = ' ';				
					area[0][*act].c = pj;
				}
			} else {
				if(area[0][*act].pos != 1){
					area[0][(*act)--].c = ' ';
					area[0][*act].c = pj;
				}
			}
		} else if(mod == 2){
			if(der){
				if(area[1][*act].pos != A - 2){
					area[0][(*act)++].c = ' ';
					area[1][*act].c = pj;
				} else {
					area[0][*act].c = ' ';
					area[1][*act].c = pj;
				}
			} else {
				if(area[1][*act].pos != 1){
					area[0][(*act)--].c = ' ';
					area[1][*act].c = pj;
				} else {
					area[0][*act].c = ' ';
					area[1][*act].c = pj;
				}
			}
		}

		return 0;
	}
