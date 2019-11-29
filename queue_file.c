#include "lem_in.h"

t_qnode		*new_node(int	key)
{
	t_qnode	*tmp = (t_qnode *)malloc(sizeof(t_qnode));
	tmp->key = key;
	tmp->next = NULL;
	return (tmp);
}

t_queue		*create_queue()
{
	t_queue	*q = (t_queue *)malloc(sizeof(t_queue));
	q->front = q->rear = NULL;
	return (q);
}

void		en_queue(t_queue *q, int key)
{
	t_qnode		*tmp;
	
	tmp = new_node(key);
	if (q->rear == NULL)
	{
		q->front = q->rear = tmp;
		return ;
	}
	q->rear->next = tmp;
	q->rear = tmp;
}

t_qnode		*de_queue(t_queue *q)
{
	t_qnode		*tmp;
	
	if (q->front == NULL)
		return (NULL);
	tmp = q->front;
	free(tmp);
	q->front = q->front->next;
	if (q->front == NULL)
		q->rear = NULL;
	return (tmp);
}

int is_empty(t_queue *q)
{
	if(q->front == NULL)
		return (1);
	else 
		return (0);
}

// int main()
// {
// 	t_queue* q = create_queue(); 
// 	en_queue(q, "10"); 
// 	en_queue(q, "20"); 
// 	de_queue(q); 
// 	de_queue(q); 
// 	en_queue(q, "30"); 
// 	en_queue(q, "40"); 
// 	en_queue(q, "50"); 
// 	t_qnode* n = de_queue(q); 
// 	if (n != NULL) 
// 		printf("Dequeued item is %s", n->key); 
// 	return 0; 
// }