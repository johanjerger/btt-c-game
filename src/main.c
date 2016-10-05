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
#include <errno.h>
#include <time.h>
#include "include/types.h"
#include "include/error.h"
#include "include/function.h"
#include "include/btt.h"


	int main()
	{
		int result = 0;
		int dif;
		int i;
		char pj;

		struct timespec ts;
	  	ts.tv_sec = 3000 / 1000;
	  	ts.tv_nsec = (3000 % 1000) * 1000000;

		block_arr area;
		for(i=0; i < L; i++){
			initialize_area(area[i]);
		}

		do{
			dif = menu();

			if(dif != 'q'){
				pj = select_pj();
				result = game(area, &dif, pj);
				
				if((system("clear")) == -1) exit(ERR_SYS);

				printf("\t\t\tGAME OVER\n\tScore : %d\n\n", result);
				
				if((nanosleep(&ts, NULL)) == -1){
					fprintf(stderr, "error -> %d\n", errno);
					exit(ERR_SYS);
				}
				
				is_high_score(result);
				
				if((nanosleep(&ts, NULL)) == -1){
					fprintf(stderr, "error -> %d\n", errno);
					exit(ERR_SYS);
				}


				for(i=0; i < L; i++){
					initialize_area(area[i]);
				}
			}

		} while((dif != 'q'));

		return 0;
	}
