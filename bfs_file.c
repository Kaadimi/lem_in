#include "lem_in.h"

// void print_queue(t_queue q) {
// 	if(is_empty(&q)) {
// 		printf("Queue is empty");
// 	} else {
// 		printf("\nQueue contains \n");
// 		while(q.front != q.rear) 
// 		{
// 			printf("%s ", q.front->key);
// 			q.front
// 		}
// 	}
// }

int		full_node(t_graph *g, int child, int parent, int cond)
{
	t_node *tmp;

	tmp = g->adjLists[parent];
	while (tmp)
	{
		if (tmp->order == child)
			if (tmp->status == cond)
			{
				tmp->status = -1;
				return (1);
			}
		tmp = tmp->next;
	}
	return (0);
}

void	visited_node(t_graph *g, int child, int parent, int cond)
{
	t_node *tmp;

	tmp = g->adjLists[parent];
	while (tmp)
	{
		if (tmp->order == child)
		{
			if (full_node(g, parent, child, cond))
			{
				tmp->status = -1;
				g->changed = 1;
			}
			else
				tmp->status = cond;
			break ;
		}
		tmp = tmp->next;
	}
}

t_path		*create_path(int order)
{
	t_path	*node;

	node = (t_path *)malloc(sizeof(t_path));
	node->path = ft_itoa(order);
	node->length = 0;
	node->next = NULL;
	return (node);
}

t_path		*trace_back(t_graph *g, int end, int cond)
{
	int		i;
	int		counter;
	t_path		*node;

	counter = 1;
	node = create_path(end);
	i = end;
	while (g->visited[i] != -2)
	{
		node->path = rev_room_join(node->path, ft_itoa(g->visited[i]), '#');
		visited_node(g, i, g->visited[i], cond);
		i = g->visited[i];
		counter++;
	}
	node->length = counter;
	return (node);
}

t_path		*ft_bfs(t_graph *g, int cond)
{
	t_queue *q;
	t_qnode *qnode;
	t_node	*n;
	int		tmp;
	
	q = create_queue();
	g->visited[0] = -2;
	en_queue(q, 0);
	while (1337)
	{
		if (!(qnode = de_queue(q)))
			break ;
		tmp = qnode->key;
		n = g->adjLists[tmp];
		//printf("visited == %s  key == %d status == %d\n", g->index[tmp], tmp, n->status);
		while (n)
		{
			//printf("possible visit == %s status == %d\n", g->index[n->order],  n->status);
			if (g->visited[n->order] == -1 && n->status != cond && n->status != -1)
			{
				//printf("actuel visit == %s  key == %d  node->key == %d\n", g->index[n->order], n->order, tmp);
				g->visited[n->order] = tmp;
				if (n->order == 1)
					return (trace_back(g, 1, cond));
				en_queue(q, n->order);
			}
			n = n->next;
		}
	}
	return (NULL);
}

void	reset_visited(t_graph *g)
{
	int		i;

	i = 0;
	while (g->visited[i] < g->length)
		g->visited[i++] = -1;
}

int		path_cross(t_path *old_path, t_path *new_path)
{
	t_path	*tmp;
	char	**tab_one;
	char	**tab_two;
	int		i;
	int		j;

	tmp = old_path;
	tab_two = ft_strsplit(new_path->path, '#');
	while (tmp)
	{
		i = 1;
		tab_one = ft_strsplit(tmp->path, '#');
		while (tab_one[i + 1])
		{
			j = 1;
			while (tab_two[j + 1])
			{
				if (!ft_strcmp(tab_one[i], tab_two[j]))
				{
					tab_free(tab_one);
					tab_free(tab_two);
					return (1);
				}
				j++;
			}
			i++;
		}
		tab_free(tab_one);
		tmp = tmp->next;
	}
	tab_free(tab_two);
	return (0);
}

int		compare_groups(t_group *gr)
{
	if ((gr->group_length[1] / gr->path_number[1])  >=
		(gr->group_length[0] / gr->path_number[0]))
	{
		free_path(&gr->gr_two);
		printf("%p  \n", &gr->groups[1]);
		return (1);
	}
	else
	{
		free_path(&gr->gr_one);
		printf("%p  \n", &gr->groups[0]);
		return (0);
	}
}

void	print_path(t_graph g, t_group *gr, t_path *path, int eog)
{
	char	**tab;
	int		i;
	static int switchG = 0;
	//t_path *tmp;
	
	i = 0;
	if (eog == 1)
	{
		if (gr->groups[0] && gr->groups[1])
			switchG = compare_groups(gr);
		else
			switchG = 1;
		return ;
	}
	//tmp = gr->groups[switchG];
	if (gr->groups[switchG] == NULL)
	{
		gr->path_number[switchG] = 1;
		gr->group_length[switchG] = path->length;
		gr->groups[switchG] = path;
		if (switchG == 0)
			gr->gr_one = gr->groups[switchG];
		else
			gr->gr_two = gr->groups[switchG];
	}
	else if (!path_cross(switchG == 1 ? gr->gr_two : gr->gr_one, path))
	{
		gr->path_number[switchG] += 1;
		gr->group_length[switchG] += path->length;
		gr->groups[switchG]->next = path;
		gr->groups[switchG] = gr->groups[switchG]->next;
	}
	tab = ft_strsplit(path->path, '#');
	//printf("path == %s\n", path->path);
	printf("path length == %zu\n", path->length);
	while (tab[i])
	{
		printf("=> %s ", g.index[ft_atoi(tab[i])]);
		i++;
	}
	printf("\n");
	tab_free(tab);
}

void	print_finish(t_group *gr)
{
	while (gr->gr_one)
	{
		printf("gr 1 paths ==>  %s\n", gr->gr_one->path);
		gr->gr_one = gr->gr_one->next;
	}
	printf("\n");
	printf("\n");
	while (gr->gr_two)
	{
		printf("gr 2 paths ==>  %s\n", gr->gr_two->path);
		gr->gr_two = gr->gr_two->next;
	}
}

int		main()
{
	t_scout *first;
	t_graph *g;
	t_path	*path;
	t_group *gr;

	gr = create_group();
	first = (t_scout *)malloc(sizeof(t_scout));
	first->nodes = 0;
	first->names = NULL;
	scouting_loop(first);
	g = create_graph(first);
	filling_loop(g, first);
	while (1337)
	{
		path = ft_bfs(g, g->flow);
		if (path == NULL && g->changed == 0)
		{
			
			printf("winner %d \n", compare_groups(gr));
			print_finish(gr);
			break ;
		}
		else if (path == NULL)
		{
			g->changed = 0;
			g->flow++;
			print_path(*g, gr, path, 1);
			printf("\n---------------------------------\n");
		}
		else
			print_path(*g, gr, path, 0);
		reset_visited(g);
	}
	if (gr->groups[0])
		printf("group 1 victory");
	if (gr->groups[1])
		printf("group 2 victory"); 
	//printf("path == %s length == %d\n", gr->gr_one->path, gr->group_length[0]);
	//printf("path == %s\n", gr->gr_one->next->path);
	//printf("------------------------------\n");
	//printf("path == %s length == %d\n", gr->gr_two->path,  gr->group_length[1]);
	//printf("path == %s\n", gr->gr_two->next->path);
}