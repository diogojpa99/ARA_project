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

void Print_List_of_Adjacencies(Nodes *listHead);

int walk_trough_nodesList(Nodes *listHead);

Nodes *wakeNode(Nodes *listHead, int awake_id);

#endif //NODES INCLUDED