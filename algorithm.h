#ifndef ALGORITHM_INCLUDED
#define ALGORITHM_INCLUDED

#include "readFile.h"

void Algorithm(Nodes *nodes_head);

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node);

Nodes *initReverseDijktra(Nodes *list_head, Nodes *destiny_node);

Queue *InsertQ(Nodes *node, Queue *Q);

Queue *CreateNewElement(Queue *new_element, Nodes *node);

Queue *RemoveNodeFromQ(Queue *Q);

Queue *Relaxation1(Queue *Q, Queue **Q2, Queue **Q3);

Queue *RelaxOfLink1(Queue *Q, Nodes *adj_node, int adj_node_type, Queue **Q2, Queue **Q3);

void ChooseQ1(Queue **Q1, Queue **Q2, Queue **Q3, Nodes *node, int type);

Queue *Relaxation2(Queue *Q, Queue **Q1, Queue **Q3);

Queue *RelaxOfLink2(Queue *Q, Nodes *adj_node, int adj_node_type, Queue **Q1, Queue **Q3);

void ChooseQ2(Queue **Q2, Queue **Q1, Queue **Q3, Nodes *node, int type);

Queue *Relaxation3(Queue *Q, Queue **Q1, Queue **Q2);

Queue *RelaxOfLink3(Queue *Q, Nodes *adj_node, int adj_node_type, Queue **Q1, Queue **Q2);

void ChooseQ3(Queue **Q3, Queue **Q1, Queue **Q2, Nodes *node, int type);

#endif //READFILE INCLUDED