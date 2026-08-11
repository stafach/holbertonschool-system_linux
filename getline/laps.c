#include "laps.h"

/**
 * find_car - Find a car in the race.
 * @car: array of car IDs
 * @count: number of cars
 * @id: car ID to find
 * Return: index of the car, or -1 if not found
 */
int find_car(int *car, int count, int id)
{
	int i;

	for (i = 0; i < count; i++)
	{
		if (car[i] == id)
			return (i);
	}
	return (-1);
}

/**
 * find_position - Find the position where a car must be inserted.
 * @car: array of car IDs
 * @count: number of cars
 * @id: car ID
 * Return: insertion position
 */
int find_position(int *car, int count, int id)
{
	int i;

	for (i = 0; i < count; i++)
	{
		if (car[i] > id)
			return (i);
	}
	return (count);
}

/**
 * shift_cars - Shift cars and laps to the right.
 * @car: array of car IDs
 * @laps: array of lap counts
 * @count: number of cars
 * @position: insertion position
 */
void shift_cars(int *car, int *laps, int count, int position)
{
	int i;

	for (i = count; i > position; i--)
	{
		car[i] = car[i - 1];
		laps[i] = laps[i - 1];
	}
}

/**
 * add_car - Add a new car at the correct position.
 * @car: pointer to car array
 * @laps: pointer to laps array
 * @count: pointer to number of cars
 * @id: new car ID
 * Return: 1 on success, 0 on failure
 */
int add_car(int **car, int **laps, int *count, int id)
{
	int *tmp_car;
	int *tmp_laps;
	int position;

	position = find_position(*car, *count, id);

	tmp_car = realloc(*car, (*count + 1) * sizeof(int));
	if (tmp_car == NULL)
		return (0);

	*car = tmp_car;

	tmp_laps = realloc(*laps, (*count + 1) * sizeof(int));
	if (tmp_laps == NULL)
		return (0);

	*laps = tmp_laps;

	shift_cars(*car, *laps, *count, position);
	(*car)[position] = id;
	(*laps)[position] = 0;
	(*count)++;

	printf("Car %d joined the race\n", id);
	return (1);
}

/**
 * print_cars - Print all cars and their laps.
 * @car: array of car IDs
 * @laps: array of lap counts
 * @count: number of cars
 */
void print_cars(int *car, int *laps, int count)
{
	int i;

	printf("Race state:\n");
	for (i = 0; i < count; i++)
		printf("Car %d [%d laps]\n", car[i], laps[i]);
}

/**
 * race_state - Keep track of cars and their laps.
 * @id: array of car IDs
 * @size: number of car IDs
 */
void race_state(int *id, size_t size)
{
	static int *car;
	static int *laps;
	static int count;
	size_t i;
	int position;

	if (size == 0)
	{
		free(car);
		free(laps);
		car = NULL;
		laps = NULL;
		count = 0;
		return;
	}

	for (i = 0; i < size; i++)
	{
		position = find_car(car, count, id[i]);
		if (position >= 0)
			laps[position]++;
		else if (!add_car(&car, &laps, &count, id[i]))
			return;
	}
	print_cars(car, laps, count);
}
