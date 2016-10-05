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
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "include/types.h"
#include "include/function.h"
#include "include/moves.h"
#include "include/verify.h"
#include "include/cheats.h"
#include "include/generate.h"
#include "include/error.h"


	int game(block_arr area, int * dif, char pj)
	{
		int key, c, i;
		int act = A/2, act_lv = 1;
		int c_shots[L], c_enem[L];
		int pnt = 0, num = 5, quit = 0, dif_n = 0, enem_n = 0, handicap = 0, der = 0;
		int is_cheat = 0, cheat_t, is_fb = 0, time_sleep = 0;
		int level = 1, enem_level = 100, e_l = 100, time = 125;
		char cheat[CH];
		fireball ball;
		struct timespec ts;
	  	ts.tv_sec = time / 1000;
	  	ts.tv_nsec = (time % 1000) * 1000000;

		for(i = 0; i < CH - 1; i++) cheat[i] = ' ';
		cheat[CH-1]= '\0';

		for(i = 0; i < L; i++) c_shots[i] = 0, c_enem[i] = 0;

		switch(*dif){
		case '1': 
			dif_n = 0; enem_n = 0;
			break;
		case '2': 
			dif_n = 2; enem_n = 5;
			break;
		case '3': 
			dif_n = 4; enem_n = 10;
			break;
		case '4': 
			dif_n = 6; enem_n = 15;
			break;
		}

		handicap = C - dif_n;
		bullet shots[L][handicap];
		enemies enem[L][MC];

		block null_area;
		null_area.pos = -1;

		area[act_lv][act].c = pj;

		draw(area);
		printf(FOOTBAR);
		printf("press 't' for the tutorial or 'q' for exit\n");

		do{
			if((key = kbhit())){
				switch(key){
				case 'd':
					is_cheat = verify_cheat(cheat, &cheat_t, key);
					if(area[act_lv][act].pos != A - 2){
						area[act_lv][act].c = ' ';
						act++;
						area[act_lv][act].c = pj;
						der = 1;
					}
					break;
				case 'a':
					is_cheat = verify_cheat(cheat, &cheat_t, key);
					if(area[act_lv][act].pos != 1){
						area[act_lv][act].c = ' ';
						act--;
						area[act_lv][act].c = pj;
						der = 0;
					}
					break;
				case 'w':
					is_cheat = verify_cheat(cheat, &cheat_t, key);
					if(act_lv == 1){
						jump(area, &act, der, pj, 0);

						for(i = 1; i < L; i++){
							if(is_fb == i){
								move_fireball(area[i], &ball, &is_fb);
							}
							move_shots(area[i], shots[i], &(c_shots[i]));
							move_enem(area[i], enem[i], &(c_enem[i]));
							if(time_sleep == 0){
								generate_enemies(area[i], enem[i], &(c_enem[i]), &num, &enem_level, &e_l, &time, &level ,enem_n, &time_sleep);
							} else {
								time_sleep--;
								if(time_sleep == 500){
									area[L/2][(A/2)-3].c = 'L';
									area[L/2][(A/2)-2].c = 'E';
									area[L/2][(A/2)-1].c = 'V';
									area[L/2][(A/2)].c = 'E';
									area[L/2][(A/2)+1].c = 'L';
									area[L/2][(A/2)+2].c = ' ';
									area[L/2][(A/2)+3].c = 'U';
									area[L/2][(A/2)+4].c = 'P';
								}
							}
							pnt += verify_shots(area[i], enem[i], shots[i], &(c_enem[i]), &(c_shots[i]), handicap);
							if(is_fb == i){
								if(i < L-1){
									pnt += verify_fireball(area[i], area[i-1], area[i+1], enem[i], enem[i-1], enem[i+1], &ball, &(c_enem[i]), &(c_enem[i-1]), &(c_enem[i+1]), &is_fb);
								} else if(i == (L-1)){
									pnt += verify_fireball(area[i], area[i-1], &null_area, enem[i], enem[i-1], enem[i-1], &ball, &(c_enem[i]), &(c_enem[i-1]), &(c_enem[i-1]), &is_fb);
								}
							}
						}
						draw(area);
						printf(FOOTBAR);
						if((nanosleep(&ts, NULL)) == -1){
							fprintf(stderr, "error -> %d\n", errno);
							exit(ERR_SYS);
						}

						jump(area, &act, der, pj, 1);

						for(i = 1; i < L; i++){
							if(is_fb == i){
								move_fireball(area[i], &ball, &is_fb);
							}
							move_shots(area[i], shots[i], &(c_shots[i]));
							move_enem(area[i], enem[i], &(c_enem[i]));
							if(time_sleep == 0){
								generate_enemies(area[i], enem[i], &(c_enem[i]), &num, &enem_level, &e_l, &time, &level ,enem_n, &time_sleep);
							} else {
								time_sleep--;
								if(time_sleep == 500){
									area[L/2][(A/2)-3].c = 'L';
									area[L/2][(A/2)-2].c = 'E';
									area[L/2][(A/2)-1].c = 'V';
									area[L/2][(A/2)].c = 'E';
									area[L/2][(A/2)+1].c = 'L';
									area[L/2][(A/2)+2].c = ' ';
									area[L/2][(A/2)+3].c = 'U';
									area[L/2][(A/2)+4].c = 'P';
								}
							}
							pnt += verify_shots(area[i], enem[i], shots[i], &(c_enem[i]), &(c_shots[i]), handicap);
							if(is_fb == i){
								if(i < L-1){
									pnt += verify_fireball(area[i], area[i-1], area[i+1], enem[i], enem[i-1], enem[i+1], &ball, &(c_enem[i]), &(c_enem[i-1]), &(c_enem[i+1]), &is_fb);
								} else if(i == (L-1)){
									pnt += verify_fireball(area[i], area[i-1], &null_area, enem[i], enem[i-1], enem[i-1], &ball, &(c_enem[i]), &(c_enem[i-1]), &(c_enem[i-1]), &is_fb);
								}
							}
						}
						draw(area);
						printf(FOOTBAR);
						if((nanosleep(&ts, NULL)) == -1){
							fprintf(stderr, "error -> %d\n", errno);
							exit(ERR_SYS);
						}

						jump(area, &act, der, pj, 2);
					} else {
						area[act_lv][act].c = ' ';
						act_lv--;
						area[act_lv][act].c = pj;
					}
					break;
				case 's':
					is_cheat = verify_cheat(cheat, &cheat_t, key);
					if(act_lv < L-1){
						area[act_lv][act].c = ' ';
						act_lv++;
						area[act_lv][act].c = pj;
					}
					break;
				case 'k':
					is_cheat = verify_cheat(cheat, &cheat_t, key);
					generate_shots(area[act_lv], &(c_shots[act_lv]), shots[act_lv], act_lv, act, handicap, der);
					break;
				case 'p':
					if((system("clear")) == -1) exit(ERR_SYS);
					
					printf("\t\t\t\tPAUSE\n");
					while(((c = getch())!='p') && (c != 'q'));
					if(c == 'q'){
						if((system("clear")) == -1){
							exit(ERR_SYS);
						}
						printf("Are you sure?[Y/N]\n");
						if(((c = getch()) == 'Y') || (c == 10) || (c == 'y')){
							quit = 1;
							*dif = 'a';
						}
					}
					break;
				case 'q':
					if((system("clear")) == -1) exit(ERR_SYS);
					
					printf("Are you sure?[Y/N]\n");
					if(((c = getch()) == 'Y') || (c == 10) || (c == 'y')){
						quit = 1;
						*dif = 'a';
					}
					break;
				case 't':
					printf("\n\t'a' -> Left\n\t'd' -> Right\n\t'w' -> Up\n\t's' -> Down\n\t'k' -> shots\n\t'p' -> pause\n\t'q' -> quit\n");
					sleep(3);
				}
			}

			if(!quit){

				if(!is_cheat){
					for(i = 1; i < L; i++){
						if(is_fb == i){
							move_fireball(area[i], &ball, &is_fb);
						}
						move_shots(area[i], shots[i], &(c_shots[i]));
						move_enem(area[i], enem[i], &(c_enem[i]));
						
						if(time_sleep == 0){
							generate_enemies(area[i], enem[i], &(c_enem[i]), &num, &enem_level, &e_l, &time, &level ,enem_n, &time_sleep);
						} else {
							time_sleep--;
							if(time_sleep == 500){
								area[L/2][(A/2)-3].c = 'L';
								area[L/2][(A/2)-2].c = 'E';
								area[L/2][(A/2)-1].c = 'V';
								area[L/2][(A/2)].c = 'E';
								area[L/2][(A/2)+1].c = 'L';
								area[L/2][(A/2)+2].c = ' ';
								area[L/2][(A/2)+3].c = 'U';
								area[L/2][(A/2)+4].c = 'P';
							}
						}

						pnt += verify_shots(area[i], enem[i], shots[i], &(c_enem[i]), &(c_shots[i]), handicap);
						if(is_fb == i){
							if(i < L-1){
								pnt += verify_fireball(area[i], area[i-1], area[i+1], enem[i], enem[i-1], enem[i+1], &ball, &(c_enem[i]), &(c_enem[i-1]), &(c_enem[i+1]), &is_fb);
							} else if(i == (L-1)){
								pnt += verify_fireball(area[i], area[i-1], &null_area, enem[i], enem[i-1], enem[i-1], &ball, &(c_enem[i]), &(c_enem[i-1]), &(c_enem[i-1]), &is_fb);
							}
						}
						if(act_lv == i){
							quit = verify_pj(enem[i], area[i], act, c_enem[i]);
							if(quit){
								*dif = 'a';
							}
						}
					}
				} else {
					switch(cheat_t){
					case 1: 
						cheat_one(area[act_lv], &(c_enem[act_lv]), &(c_shots[act_lv]), act, pj);
						break;
					case 2:
						cheat_two(area[act_lv], &(c_enem[act_lv]), &(c_shots[act_lv]), act, pj);
						break;
					case 3:
						cheat_three(area[act_lv], &(c_enem[act_lv]), &(c_shots[act_lv]), act, pj);
						break;
					case 4:
						if(!is_fb){
							cheat_four(area[act_lv], &ball, act, der);
						}
						is_fb = act_lv;
						break;
					}
					is_cheat = 0;
				}

				ts.tv_sec = time / 1000;
	  			ts.tv_nsec = (time % 1000) * 1000000;
				
				draw(area);
				printf(FOOTBAR);
				if((nanosleep(&ts, NULL)) == -1){
					fprintf(stderr, "error -> %d\n", errno);
					exit(ERR_SYS);
				}
			} else {
				time_sleep--;
			}

		} while(!quit);

		return pnt;
	}
	