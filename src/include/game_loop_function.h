#ifndef BTT_GLF_H
#define BTT_GLF_H

	int printf_footbar(int, int *, int, int, int *);

	int level_up_messege(block_arr);

	int horizontal_move(int, int, int, block_arr, int, int *, int, int *);
	
	int move_operations(block *, bullet *, enemies *, fireball *, int *, 
						 int *, int *, int);

	int generate_enemies_control(block *, enemies *, int  *, int *, int *,
								 int *, int *, int *, int, int *, block_arr);

	int fireball_control(int *, int, int *, block *, block *, block *, enemies *, 
						 enemies *, enemies *, fireball *, int *, int *, int *, 
						 block *);

#endif
