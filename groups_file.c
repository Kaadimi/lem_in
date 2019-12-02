#include "lem_in.h"

t_group		*create_group()
{
	t_group *gr;

	gr = (t_group *)malloc(sizeof(t_group));
	gr->groups = malloc(sizeof(t_path) * 2);
	gr->groups[0] =  NULL;
	gr->groups[1] = NULL;
	gr->gr_one = NULL;
	gr->gr_two = NULL;
	gr->group_length = (int *)malloc(sizeof(int) * 2);
	gr->path_number = (int *)malloc(sizeof(int) * 2);
	gr->group_length[0] = gr->group_length[1] = 0;
	gr->path_number[0] = gr->path_number[1] = 0;	
	return (gr);
}

void		free_path(t_path **path)
{
	t_path *tmp;

	while (*path)
	{
		tmp = (*path)->next;
		free((*path)->path);
		free(*path);
		*path = tmp;
		printf("wtfff\n");
	}
	*path = NULL;
}