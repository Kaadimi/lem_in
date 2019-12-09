#include "lem_in.h"

void	tab_free(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
		ft_strdel(&tabs[i++]);
	free(tabs);
}

size_t		split_finder(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char		*room_join(char *s1, const char *s2, char c)
{
	char	*fr;
	size_t	v;

	if (!s1 || !s2)
		return (NULL);
	v = ft_strlen(s1) + ft_strlen(s2);
	if (!(fr = ft_strnew(v + 2)))
		return (NULL);
	ft_strcpy(fr, s1);
	fr[ft_strlen(s1)] = c;
	fr[ft_strlen(s1) + 1] = '\0';
	ft_strcat(fr, s2);
	ft_strdel(&s1);
	s1 = NULL;
	return (fr);
}

char		*rev_room_join(char *s1, const char *s2, char c)
{
	char	*fr;
	size_t	v;

	if (!s1 || !s2)
		return (NULL);
	v = ft_strlen(s1) + ft_strlen(s2);
	if (!(fr = ft_strnew(v + 2)))
		return (NULL);
	ft_strcpy(fr, s2);
	fr[ft_strlen(s2)] = c;
	ft_strcat(fr, s1);
	ft_strdel(&s1);
	s1 = NULL;
	return (fr);
}

t_node		*create_node(int order)
{
	t_node *n;
	
	n = (t_node *)malloc(sizeof(t_node));
	n->status = 0;
	n->order = order;
	n->next = NULL;
	return (n);
}

t_graph		*create_graph(t_scout *start)
{
	t_graph	*g;
	char	**tab;
	int		i;
	
	i = 0;
	g = malloc(sizeof(t_graph));
	g->length = start->nodes;
	g->changed = 0;
	g->flow = 1;
	g->ants = start->ants;
	g->adjLists = malloc((start->nodes + 1) * sizeof(t_node));
	g->visited = malloc(start->nodes * sizeof(int));

	start->names = rev_room_join(start->names, start->end, '#');
	start->names = rev_room_join(start->names, start->start, '#');
	printf("line == %s\n", start->names);
	g->index = ft_strsplit(start->names, '#');

	while (i < start->nodes)
	{
		g->adjLists[i] = create_node(i);
		g->visited[i] = -1;
		i++;
	}
	g->adjLists[i] = NULL;
	return (g);
}

int		name_exist(t_scout first, char	*n1)
{
	char	**tab;
	int		i;

	i = 0;
	if (first.names == NULL)
		return (0);
	tab = ft_strsplit(first.names, '#');
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], n1))
			return (1);
		i++;
	}
	return (0);
}

int		get_start(t_scout	*first)
{
	char	*line;

	if (!ft_strcmp(line, "##start"))
	{
		if (get_next_line(0, &line))
		{
			line[split_finder(line, ' ')] = '\0';
			first->start = ft_strdup(line);
			first->nodes++;
		}
		else
			return (0);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		if (get_next_line(0, &line))
		{
			line[split_finder(line, ' ')] = '\0';
			first->end = ft_strdup(line);
			first->nodes++;
		}
		else
			return (0);
	}
	return (1);
}

int			position_lines(char *line)
{
	int i;
	int	s;

	i = s = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			s++;
		i++;
	}
	if (s == 2)
		return (1);
	return (0);
}

int		scouting_loop(t_scout	*first)
{
	int ret = 1;
	char 	*line;
	char	**tab;

	first->file = NULL;
	while ((ret = get_next_line(0, &line)))
	{
		if (first->file == NULL)
		{
			if (!(first->ants = ft_atoi(line)))
				return (0);
			first->file = ft_strdup(line);
		}
		else
			first->file = room_join(first->file, line, '\n');
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
		{
			if (!get_start(first))
				return (0);
		}
		else if (position_lines(line))
		{
			line[split_finder(line, ' ')] = '\0';
			if (!name_exist(*first, line))
			{
				if (first->nodes == 0)
					first->names = ft_strdup(line);
				else
					first->names = room_join(first->names, line, '#');
				first->nodes++;
			}
		}
		free(line);
	}
	return (1);
}

int		index_of_graph(t_graph g, char *str)
{
	int i;

	i = 0;
	while (g.index[i])
	{
		if (!ft_strcmp(g.index[i], str))
			return (i);
		i++;
	}
	return (-1);
}

int		get_file_line(t_scout *first, char **line, int *eor)
{
	int i;

	i = 0;
	if (first->file[*eor] == '\0' || !first->file)
		return (0);
	if (first->file[*eor] == '\n')
		*eor += 1;
	i = *eor;
	while (first->file[*eor] != '\n' && first->file[*eor])
		*eor += 1;
	*line = ft_strsub(first->file, i, *eor - i);
	return (1);
}

int		filling_loop(t_graph *g, t_scout *first)
{
	int ret = 1;
	char 	*line;
	char	**tab;
	int		eor;
	int		check = 0;
	t_node	*n;

	eor = 0;
	while ((ret = get_file_line(first, &line, &eor)))
	{
		if (ft_strchr(line, '-'))
		{
			tab = ft_strsplit(line, '-');
			check = index_of_graph(*g, tab[0]);
			if (check == -1)
			{
				tab_free(tab);
				return (0);
			}
			n = create_node(index_of_graph(*g, tab[1]));
			n->next = g->adjLists[check]->next;
			g->adjLists[check]->next = n;
			
			check = index_of_graph(*g, tab[1]);
			if (check == -1)
			{
				tab_free(tab);
				return (0);
			}
			n = create_node(index_of_graph(*g, tab[0]));
			n->next = g->adjLists[check]->next;
			g->adjLists[check]->next = n;
			tab_free(tab);
		}
		free(line);
		line = NULL;
	}
	return (1);
}

// int main()
// {
// 	t_scout *first;
// 	t_graph *g;

// 	first = (t_scout *)malloc(sizeof(t_scout));
// 	first->nodes = 0;
// 	first->names = NULL;
// 	scouting_loop(first);
// 	g = create_graph(first);
// 	filling_loop(g, first);
// 	int i = 0;
// 	while (g->adjLists[i])
// 	{
// 		while (g->adjLists[i])
// 		{
// 			printf("%s  -> ", g->index[g->adjLists[i]->order]);
// 			g->adjLists[i] = g->adjLists[i]->next;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }