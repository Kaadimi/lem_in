#include "lem_in.h"

t_graph     *create_graph(int vertices)
{
    t_graph *g;
    int     i;
    
    i = 0;
    g = malloc(sizeof(t_graph));
    g->numVertices = vertices;
    g->adjLists = malloc(vertices * sizeof(t_node));
    while (i < vertices)
        g->adjLists[i++] = NULL;
    return (g);
}

t_node      *create_node(int v)
{
    t_node *n = malloc(sizeof(t_node));
    n->vertex = v;
    n->next = NULL;
    return (n);
}

void    addEdge(t_graph *g, int src, int dest)
{
    t_node *n = create_node(dest);
    n->next = g->adjLists[src];
    g->adjLists[src] = n;
}

void printGraph(t_graph *graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        t_node *temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

t_queue     *createQueue() {
    t_queue *q = malloc(sizeof(t_queue));

    q->front = -1;
    q->rear = -1;
    return q;
}
int isEmpty(t_queue *q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}
void enqueue(t_queue *q, int value){
    if(q->rear == SIZE-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}
int dequeue(t_queue *q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}
void printQueue(t_queue *q) {
    int i = q->front;
    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }    
}

void bfs(t_graph *graph, int startVertex) {
    t_queue *q = createQueue();
    
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    while(!isEmpty(q)){
        printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
    
       t_node   *temp = graph->adjLists[currentVertex];
    
       while(temp) {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
    }
}

int main()
{
    t_graph *graph = create_graph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 6);
    addEdge(graph, 5, 1);
    addEdge(graph, 5, 6);
 
    bfs(graph, 0);
 
    return 0;
}