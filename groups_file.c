#include "lem_in.h"

t_group		*create_group()
{
	t_group *gr;

	gr = (t_group *)malloc(sizeof(t_group));
	gr->groups = malloc(sizeof(t_path) * 2);
	gr->groups[0] =  NULL;
	gr->groups[1] = NULL;
	return (gr);
}