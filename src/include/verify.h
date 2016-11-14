#ifndef BTT_VER_H
#define BTT_VER_H

	short verify_shots(block *, enemies *, bullet *, int *, int *, int);

	short verify_player(enemies *, block *, int, int);

	short verify_cheat(char *, int *, char);

  	short verify_fireball(block *, block *, block *, enemies *, 
  						enemies *, enemies *, fireball *, int *, 
  						int *, int *, int *);
	
#endif