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
			if (tmp->status == cond ? 0 : 1)
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
				tmp->status = cond ? 0 : 1;
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
	return (node);
}

t_path		*trace_back(t_graph *g, int end, int cond)
{
	int		i;
	int		counter;
	//t_node	*path;
	//t_node	*edges;
	t_path		*node;

	counter = 1;
	node = create_path(end);
	i = end;
	//path = create_node(1);
	//printf("%s => ", g->index[1]);
	while (g->visited[i] != -2)
	{
		node->path = rev_room_join(node->path, ft_itoa(g->visited[i]), '#');
		// edges = create_node(g->visited[i]);
		// edges->n_length = counter;
		// edges->next = path;
		// path = edges;
		//printf("%s => ", g->index[g->visited[i]]);
		visited_node(g, i, g->visited[i], cond);
		i = g->visited[i];
		counter++;
	}
	//printf("%s\n", node->path);
	node->length = counter;
	printf("\n");
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
			if (g->visited[n->order] == -1 && n->status == cond)
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

void	print_path(t_graph g, t_group *gr, t_path *path, int eog)
{
	char	**tab;
	int		i;
	
	i = 0;
	if (gr->groups[0] == NULL)
	{
		gr->groups[0] = path;
	}
	tab = ft_strsplit(path->path, '#');
	//printf("path == %s\n", path->path);
	printf("path length == %zu\n", path->length);
	while (tab[i])
	{
		printf("=> %s ", g.index[ft_atoi(tab[i])]);
		i++;
	}
	tab_free(tab);
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
			break ;
		else if (path == NULL)
		{
			g->changed = 0;
			g->flow = g->flow ? 0 : 1;
			print_path(*g, gr, path, 1);
			printf("\n---------------------------------\n");
		}
		else
			print_path(*g, gr, path, 0);
		reset_visited(g);
	}
}