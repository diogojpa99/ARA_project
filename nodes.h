#ifndef NODES_INCLUDED
#define NODES_INCLUDED



#include "readFile.h"
#include "calendar.h"

//Nodes

Nodes *createGraph(Nodes *listHead, int tail, int head, int type);

Nodes *createNode(Nodes *listHead, int tail);

Adj *createAdj(Adj *listHead, int tail, int head, int type);

Adj *insertAdj(Adj *listHead, Adj *newAdj);

Nodes *insertNode(Nodes *listHead, Nodes *newNode, int id);

Nodes *searchNodesList(Nodes *listHead, int id);

void Print_List_of_Adjacencies(Nodes *list_Head);

DestNode *updateDestToNode(Nodes *process_node, int *message, int type);

DestNode *searchDestiny(DestNode *dest_head, int dest_id);

DestNode *createDestiny(DestNode *dest_head, int neigbour_id, int dest_id, int cost, int type);

#endif //NODES INCLUDED