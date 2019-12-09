#include "lem_in.h"

int	ft_tag_atoi(const char *str)
{
	int i;
	int negatif;
	int k;
	int result;

	i = 0;
	negatif = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			negatif = 1;
	k = str[i] - '0';
	while (k >= 0 && k <= 9 && str[i] != '\0' && str[i] != '#')
	{
		result = result * 10 + k;
		i++;
		k = str[i] - '0';
	}
	if (negatif)
		result *= -1;
	return (result);
}

int		path_split(char *path, int *start)
{
	int index;

	index = *start;
	while (path[*start] != '#' && path[*start])
		*start += 1;
	return (ft_tag_atoi(path + index));
}

t_ant		*ant_maker(int last_move, int path)
{
	t_ant	*new;

	new = malloc(sizeof(t_ant));
	new->last_move = last_move;
	new->path = path;
	return (new);
}

t_bridge	*make_bridge(t_path	*path, int n_paths, int ants)
{
	t_bridge	*b;
	int			i;
	int			s;
	int			path_index;
	t_ant		*fuck;

	printf("testing1 %d   %d\n", n_paths, ants);
	if (!(b = malloc(sizeof(t_bridge))))
		return (NULL);
	b->ants = malloc(sizeof(t_ant) * ants);
	i = 0;
	while (i < ants)
		b->ants[i++] = ant_maker(-1, 0);
	if (!(b->paths = malloc(sizeof(int *) * n_paths)))
		return (NULL);
	path_index = 0;
	while (path)
	{
		s = 0;
		i = 0;
		b->paths[path_index] = (int *)malloc(sizeof(int) * path->length);
		while (i < path->length)
		{
			b->paths[path_index][i] = path_split(path->path, &s);
			i++;
			s++; 
		}
		path_index++;
		path = path->next;
	}
	b->nb_paths = n_paths;
	printf("testing1  \n");
	return (b);
}

#define L_MOVE (b->ants[ant]->last_move)
#define PATH (b->ants[ant]->path)

int		ant_movements(t_bridge *b, t_graph *g, int index, int ant)
{
	int i;

	if (L_MOVE == -1)
	{
		i = 0;
		while (i < b->nb_paths)
		{
			if (g->visited[b->paths[i][1]] == -1)
			{
				L_MOVE = 1;
				PATH = i;
				g->visited[b->paths[i][1]] = ant;
				return (b->paths[i][1]);
			}
			i++;
		}
		return (-1);
	}
	else
	{
		if (b->paths[PATH][L_MOVE + 1] == 1)
		{
			g->visited[b->paths[PATH][L_MOVE]] = -1;
			return (-2);
		}
		if (g->visited[b->paths[PATH][L_MOVE + 1]] == -1)
		{
			g->visited[b->paths[PATH][L_MOVE]] = -1;
			L_MOVE += 1;
			g->visited[b->paths[PATH][L_MOVE]] = ant;
			return (b->paths[PATH][L_MOVE]);
		}
		return (-1);
	}
}

void	print_move(char **index, int ant, int move)
{
	write(1, "L", 1);
	ft_putnbr(ant + 1);
	write(1, "-", 1);
	ft_putstr(index[move]);
	write(1, " ", 1);
}

void	print_tab(t_bridge *b)
{
	int i;
	int j;

	i = 0;
	while (i < b->nb_paths)
	{
		j = 0;
		while (j < 6)
		{
			printf("%d  ", b->paths[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	passing_ants(t_graph *g, t_group *gr, int index)
{
	int i;
	int	j;
	int	move;
	t_bridge *b;

	reset_visited(g);
	if (index == 0)
		b = make_bridge(gr->gr_one, gr->path_number[index], g->ants);
	else if (index == 1)
		b = make_bridge(gr->gr_two, gr->path_number[index], g->ants);
	//print_tab(b);
	j = 0;
	while (1337)
	{
		i = j;
		while (i < g->ants)
		{
			move = ant_movements(b, g, index, i);
			if (move == -2)
			{
				j++;
				print_move(g->index, i, 1);
			}
			else if (move == -1)
				break ;
			else
				print_move(g->index, i, move);
			i++;
		}
		write(1, "\n", 1);
		if (j >= g->ants)
			return ;
	}
}