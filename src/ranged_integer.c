/***************************************************************************
*
*				 «©Copyright 2016-2018 Juan Cruz Ocampos»
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
#include <stdlib.h>
#include "include/ranged_integer.h"

void
ranged_integer_inc (ranged_int_t * self)
{
		if (self->value < self->max) self->value++;
		else self->value = self->min;
}

void
ranged_integer_dec (ranged_int_t * self)
{
		if (self->value > self->min) self->value--;
		else self->value = self->max;
}

ranged_int_t *
new_ranged_int (int value, int min, int max)
{
		ranged_int_t * new_r_int;
		new_r_int = (ranged_int_t *) malloc(sizeof(ranged_int_t));

		new_r_int->value = value;
		new_r_int->min = min;
		new_r_int->max = max;
		new_r_int->inc = ranged_integer_inc;
		new_r_int->dec = ranged_integer_dec;

		return new_r_int;
}
