/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:14:27 by ikadimi           #+#    #+#             */
/*   Updated: 2019/11/21 13:28:25 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# define BUFF_SIZE 5000

typedef struct		s_scout
{
	int				ants;
	char			*file;
	int				nodes;
	char			*names;
	char			*start;
	char			*end;
}					t_scout;

typedef struct		s_qnode
{
	int				key;
	struct s_qnode	*next;
}					t_qnode;

typedef struct		s_queue
{
	t_qnode			*rear;
	t_qnode			*front;
}					t_queue;

typedef struct		s_gnl
{
	int				ret;
	int				i;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
}					t_gnl;

typedef struct		s_node
{
	size_t			n_length;
	int				status;
	int				order;
	struct s_node	*next;
}					t_node;

typedef struct		s_graph
{
	int				ants;
	int				flow;
	int				changed;
	char			**index;
	int				length;
	t_node			**adjLists;
	int				*visited;
}					t_graph;

typedef struct		s_path
{
	char			*path;
	size_t			length;
	struct s_path	*next;
}					t_path;

typedef struct		s_group
{
	t_path			*gr_one;
	t_path			*gr_two;
	int				*path_number;
	int				*group_length;
	t_path			**groups;
}					t_group;

typedef struct		s_ant
{
	int				last_move;
	int				path;
}					t_ant;

typedef struct		s_bridge
{
	int				**paths;
	int				nb_paths;
	t_ant			**ants;
}					t_bridge;

int					get_next_line(const int fd, char **line);
char				*ft_freejoin(char *s1, char *s2);
int					scouting_loop(t_scout	*first);
int					filling_loop(t_graph *g, t_scout *first);
t_graph				*create_graph(t_scout *start);
t_queue				*create_queue();
void				en_queue(t_queue *q, int key);
t_qnode				*de_queue(t_queue *q);
int					index_of_graph(t_graph g, char *str);
int					is_empty(t_queue *q);
t_node				*create_node(int order);
char				*rev_room_join(char *s1, const char *s2, char c);
void				tab_free(char **tabs);
t_group				*create_group();
void				free_path(t_path **path);
void				reset_visited(t_graph *g);
void				passing_ants(t_graph *g, t_group *gr, int index);
void				print_finish(t_group *gr);

#endif
