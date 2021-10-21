#ifndef ALGORITHM_INCLUDED
#define ALGORITHM_INCLUDED

#include "readFile.h"

void Algorithm(Nodes *nodes_head, int destiny_id);

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node);

Nodes *initReverseDijktra(Nodes *list_head, Nodes *destiny_node);

Queue *InsertQ(Nodes *node, Queue *Q);

Queue *CreateNewElement(Queue *new_element, Nodes *node);

Queue *RemoveTopNodeFromQ(Queue *Q);

Queue *Relaxation(Queue *Q, Queue *Q1, Queue *Q2, Queue *Q3);

Queue *RelaxOfLink(Queue *Q, Nodes *adj_node, int adj_node_type, Queue *Q1, Queue *Q2, Queue *Q3);

void ChooseQ(Queue *Q1,Queue *Q2,Queue *Q3, Nodes *node, int type);

#endif //READFILE INCLUDED