#ifndef BTT_R_INT_H
#define BTT_R_INT_H

typedef struct _ranged_integer
{
        int value;
        int max;
        int min;
        void (*inc)(struct _ranged_integer *);
        void (*dec)(struct _ranged_integer *);
} ranged_int_t;

ranged_int_t * new_ranged_int(int, int, int);

#endif
