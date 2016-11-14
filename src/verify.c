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
#include "include/types.h"

	
	static short cmp_fireball(block * area, enemies * enem, fireball * ball, 
							int * cnt_enem)
	{
		short arr_en[MC];
		short i, j, k = 0, len = 0;
		short points = 0;

		for(i = 0; i < *cnt_enem; i++){
			if(enem[i].pos == ball->pos || enem[i].pos == ball->pos+1 || enem[i].pos == ball->pos-1){
				arr_en[k] = i;
				len++;
				points += 100;
				k++;
			}
		}
		for(i = 0; i < len; i++){
			j = arr_en[i];
			area[enem[j].pos].c = 'x';
			if(i < MC - 1){
				for(k = j; k < *cnt_enem; k++){
					enem[k].pos = enem[k+1].pos;
					enem[k].der = enem[k+1].der;
				}
			}
			(*cnt_enem)--;
		}

		return points;
	}


	short verify_shots(block * area, enemies * enem, bullet * shots, 
					 int * cnt_enem, int * cnt_shots, int handicap)
  	{
		short points = 0;
		short i, j, k = 0;
		short arr_en[MC];
		short arr_sh[handicap];
		short len = 0;

		for(i = 0; i < *cnt_enem; i++){
			for(j = 0; j < *cnt_shots; j++){
				if((enem[i].pos == shots[j].pos) || (enem[i].pos == (shots[j].pos + 1)) || (enem[i].pos == (shots[j].pos - 1))){
					arr_en[k] = i;
					arr_sh[k] = j;
					len++;
					points += 100;
					k++;
				}
			}
		}
		for(i = 0; i < len; i++){
			j = arr_en[i];
			area[enem[j].pos - i].c = ' ';
			if(i < MC - 1){
				for(k = j; k < (*cnt_enem)-1; k++){
					enem[k].pos = enem[k+1].pos;
					enem[k].der = enem[k+1].der;
				}
			}
			(*cnt_enem)--;
			j = arr_sh[i];
			area[shots[j].pos - i].c = ' ';
			if(i < handicap - 1){
				for(k = j; k < (*cnt_shots)-1; k++){
					shots[k].pos = shots[k+1].pos;
					shots[k].der = shots[k+1].der;
				}
			}
			(*cnt_shots)--;
		}

		return points;
	}


	short verify_player(enemies * enem, block * area, int act, int cnt_enem)
  	{
		short kill = 0;
		short j;

		for(j = 0; j < cnt_enem; j++){
			if(enem[j].der){
				if((enem[j].pos == area[act].pos) || (enem[j].pos == area[act+1].pos)){
					kill = 1;
				}
			} else {
				if((enem[j].pos == area[act].pos) || (enem[j].pos == area[act-1].pos)){
					kill = 1;
				}
			}
		}

		return kill;
	}


	short verify_cheat(char * cheat, int * type, char key)
  	{
		short i;
		cheat[CH-1] = key;
		for(i = 0; i < 	CH - 1; i++){
			cheat[i] = cheat[i+1];
		}
		cheat[CH-1] = '\0';
		if(!strcmp(cheat, "adkda")){
			*type = 1;
			return 1;
		}
		if((!strcmp(cheat, "akdda")) || (!strcmp(cheat, "dkaad"))){
			*type = 2;
			return 1;
		}

		return 0;
	}


	short verify_fireball(block * area_act, block * area_top, block * area_lower, 
						enemies * enem_act, enemies * enem_top, enemies * enem_lower, 
						fireball * ball, int * cnt_enem_act, int * cnt_enem_top, 
						int * cnt_enem_lower, int * is_fireball)
  	{
		short points = 0;
		short i, j;
		short aux = 0;
		if(ball->mod == 0){
			for(i = 0; i < *cnt_enem_act; i++){
				if((enem_act[i].pos == ball->pos) || (enem_act[i].pos == (ball->pos + 1)) || (enem_act[i].pos == (ball->pos - 1))){
					area_act[ball->pos].c = ' ';
					ball->is_imp = 1;
					ball->mod = 1;
					area_act[enem_act[i].pos].c = 'x';
					ball->pos = enem_act[i].pos;
					aux = i;
					points += 100;
					break;
				}
			}
			if((ball->is_imp) && (aux < MC - 1)){
				for(j = aux; j < *cnt_enem_act; j++){
					enem_act[j].pos = enem_act[j+1].pos;
					enem_act[j].der = enem_act[j+1].der;
				}
				(*cnt_enem_act)--;
			}
		} else if(ball->mod == 1){
			ball->mod = 2;
			area_act[ball->pos].c = 'x';
			area_act[ball->pos-1].c = 'x';
			area_act[ball->pos+1].c = 'x';
			area_top[ball->pos].c = 'x';
			area_top[ball->pos+1].c = 'x';
			area_top[ball->pos-1].c = 'x';
			if(area_lower->pos != -1){
				area_lower[ball->pos].c = 'x';
				area_lower[ball->pos+1].c = 'x';
				area_lower[ball->pos-1].c = 'x';
			}
			points += cmp_fireball(area_act, enem_act, ball, cnt_enem_act);
			points += cmp_fireball(area_top, enem_top, ball, cnt_enem_top);
			if(area_lower->pos != -1){
				points += cmp_fireball(area_lower, enem_lower, ball, cnt_enem_lower);
			}

		} else if(ball->mod == 2){
			ball->mod = 3;
			area_act[ball->pos].c = ' ';
			
			points += cmp_fireball(area_act, enem_act, ball, cnt_enem_act);
			points += cmp_fireball(area_top, enem_top, ball, cnt_enem_top);
			if(area_lower->pos != -1){
				points += cmp_fireball(area_lower, enem_lower, ball, cnt_enem_lower);
			}
		
		} else if(ball->mod == 3){
			ball->mod = 0;
      		ball->is_imp = 0;
			area_act[ball->pos-1].c = ' ';
			area_act[ball->pos+1].c = ' ';
			area_top[ball->pos].c = ' ';
			area_top[ball->pos+1].c = ' ';
			area_top[ball->pos-1].c = ' ';
			if(area_lower->pos != -1){
				area_lower[ball->pos].c = ' ';
				area_lower[ball->pos+1].c = ' ';
				area_lower[ball->pos-1].c = ' ';
			}
      		*is_fireball = 0;
		}

		return points;
	}