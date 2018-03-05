#ifndef BTT_VER_H
#define BTT_VER_H

#include <stdbool.h>

short verify_shots(block *, enemies *, bullet *, int *, int *, int);

bool verify_player(enemies *, block *, int, int);

short verify_cheat(char *, char);

short verify_fireball(block *, block *, block *, enemies *, enemies *,
																						enemies *, fireball *, int *,
																						int *, int *, int *);
#endif
