#ifndef ALGORITHM_INCLUDED
#define ALGORITHM_INCLUDED

#include "readFile.h"

void Algorithm(Nodes *nodes_head);

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node);

Nodes *initAlgorithm(Nodes *list_head, Nodes *destiny_node);

Nodes *initReverseDijkstra(Nodes *list_head, Nodes *destiny_node);

Queue *InsertQ(Nodes *node, Queue *Q);

Queue *CreateNewElement(Queue *new_element, Nodes *node);

//Queue *RemoveNodeFromQ(Queue *Q);

Queue *Relaxation(Queue *Q, Queue **Q1, Queue **Q2, Queue **Q3);

Queue *RelaxOfLink(Queue *Q, Nodes *adj_node, int adj_node_type, Queue **Q1, Queue **Q2, Queue **Q3);

void ChooseQ(Queue **Q1, Queue **Q2, Queue **Q3, Nodes *node, int type);

void PrintQ(Queue *Q);

FILE *Print_Destinations(Nodes *nodes_Head, FILE *fd);

FILE *Print_CCDF(Nodes *nodes_Head, FILE *fd);

#endif //READFILE INCLUDED