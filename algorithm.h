#ifndef ALGORITHM_INCLUDED
#define ALGORITHM_INCLUDED

#include "readFile.h"
#include "nodes.h"

void Algorithm(Nodes *nodes_head, int destiny_id);

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node);

Nodes *initReverseDijktra(Nodes *list_head, Nodes *destiny_node);

Queue *InsertQ(Nodes *node, Queue *Q);

Queue *CreateNewElement(Queue *new_element, Nodes *node);

#endif //READFILE INCLUDED