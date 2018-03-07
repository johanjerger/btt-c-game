#ifndef BTT_GLF_H
#define BTT_GLF_H

void printf_footbar(int, int *, int, int, int *);

void level_up_messege(block_arr);

void horizontal_move(int, block_arr, int, int *, int);

void move_operations(block *, bullet *, enemies *, fireball *, int *,
																					int *, int *, int);

void generate_enemies_control(block *, enemies *, int  *, int *, int *, int *,
																														int, int *, block_arr);

void fireball_control(int *, int, int *, block_arr, enemies[10][10], fireball *, int [10]);

#endif
