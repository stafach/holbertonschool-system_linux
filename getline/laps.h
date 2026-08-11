#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void race_state(int *id, size_t size);
int find_car(int *car, int count, int id);
int find_position(int *car, int count, int id);
void shift_cars(int *car, int *laps, int count, int position);
int add_car(int **car, int **laps, int *count, int id);
void print_cars(int *car, int *laps, int count);


#endif
