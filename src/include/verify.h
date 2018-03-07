#ifndef BTT_VER_H
#define BTT_VER_H

#include <stdbool.h>

short verify_shots(block *, enemies *, bullet *, int *, int *);

bool verify_player(enemies *, block *, int, int);

short verify_cheat(char *, char);

short verify_fireball(int, block_arr, enemies[10][10], fireball *, int[10], int *);

#endif
