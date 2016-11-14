#ifndef BBT_TYPES_H
#define BBT_TYPES_H

	#define A 80		// Area length.
	#define L 10		// Area higth.
	#define C 10		// Shot max quantity per array "level".
	#define MT 20		// Mounster time appearance.
	#define MC 15		// Mounster quantity per array "level".
	#define TB 10		// Size of score table.
	#define CH 6		// Cheats string length.

	// Defining some MACROSS for the printf caracters colour.

	#define RED     "\x1b[31m"
	#define GREEN   "\x1b[32m"
	#define YELLOW  "\x1b[33m"
	#define BLUE    "\x1b[34m"
	#define MAGENTA "\x1b[35m"
	#define CYAN    "\x1b[36m"
	#define RESET   "\x1b[0m"

	/* 
		Defining the struct of every single position	
	   	in the matrix.
	*/

	typedef struct 		
	{
		char c;
		short pos;
	} block;

	typedef block block_arr[L][A+1]; // The matrix Area. 

	// Defining the enemy and bullet's struct.
	   
	typedef struct
	{
		short pos;
		short der;
	} bullet, enemies;

	// Score tab slots struct.

	typedef struct
	{
		char name[16];
		int point;
		short level;
		char difficulty[16];
	} score;

	/* 
		Fireball char struct, the mod is for
	   	control & know the actual state of
	   	the fireball in the area, & is_imp
	   	for know if this implote or not.
	*/

	typedef struct
	{
		short mod;
		short pos;
		short is_imp;
		short der;
	} fireball;

	/* 
		This five "enums" are uses in
		menu.c for control who is the
		current option
	*/

	enum 
	{
		START_GAME,
		SCORE_TAB,
		HISTORY,
		TUTORIAL,
		EXIT
	};

	enum 
	{
		EASY,
		NORMAL,
		HARD,
		VERY_HARD,
		HOPELESS
	};

	enum
	{
		FIRST,
		SECOND,
		THIRD
	};

	enum 
	{
		MENU,
		CLEAN
	};

	enum
	{
		RESUME,
		QUIT
	};

#endif
