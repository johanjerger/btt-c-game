#ifndef BTT_FUNC_H
#define BTT_FUNC_H

#define FOOTBAR "\nRemaining shots : %d\t\tPoints : %d\n\t   Level : %d\n", handicap - c_shots[act_lv], pnt, level

	int getch();

	int kbhit();

	int menu();

	char select_pj();

	int initialize_area(block *);

	int is_high_score(int);

	int draw(block_arr);

	int move_shots(block *, bullet *, int *);

	int move_enem(block *, enemies *, int *);

#endif
