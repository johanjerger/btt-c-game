#ifndef BBT_TYPES_H
#define BBT_TYPES_H


	#define A 80		//area len
	#define L 10		//area higth
	#define C 10		//shot cant
	#define MT 20		//mounster time
	#define MC 15		//mounster cant
	#define TB 10		//size off score table
	#define CH 6		//cheats len

	#define RED     "\x1b[31m"
	#define GREEN   "\x1b[32m"
	#define YELLOW  "\x1b[33m"
	#define BLUE    "\x1b[34m"
	#define MAGENTA "\x1b[35m"
	#define CYAN    "\x1b[36m"
	#define RESET   "\x1b[0m"

	typedef struct
	{
		char c;
		int pos;
	} block;

	typedef block block_arr[L][A+1];

	typedef struct
	{
		int pos;
		int der;
	} bullet, enemies;

	typedef struct
	{
		char name[256];
		int point;
	} score;

	typedef struct
	{
		int mod;
		int pos;
		int is_imp;
		int der;
	} fireball;

#endif
